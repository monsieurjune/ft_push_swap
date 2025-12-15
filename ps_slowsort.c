/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_slowsort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:56:28 by tponutha          #+#    #+#             */
/*   Updated: 2023/04/12 04:37:34 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	sb_find_next_min(t_stack a, int high, long pmin)
{
	int	min;

	min = INT_MAX;
	while (1)
	{
		if (a.head->value < min && a.head->value > pmin)
		{
			min = a.head->value;
		}
		if (a.head->value == high)
			break ;
		a.head = a.head->next;
	}
	return (min);
}

// not actual median, just near (for working with 5)

static int	sb_median_pivot(t_stack a, int high)
{
	long	pmin;
	int		med;
	int		i;

	i = (ps_bottom_index(a, high) + 2) / 2;
	pmin = LONG_MIN;
	while (i > 0)
	{
		med = sb_find_next_min(a, high, pmin);
		pmin = med;
		i--;
	}
	return (med);
}

static int	sb_find_less(t_stack a, int pivot)
{
	int	i;

	i = 1;
	if (a.head == NULL)
		return (0);
	while (a.head != a.tail && a.head->prev != a.tail)
	{
		if (a.head->value < pivot)
			return (i);
		a.head = a.head->next;
		if (a.tail->value < pivot)
			return (-1 * i);
		a.tail = a.tail->prev;
		i++;
	}
	if (a.head->value < pivot)
		return (i);
	return (0);
}

static int	sb_partition(t_stack *a, t_stack *b, int high)
{
	int	n;
	int	less;
	int	pivot;

	n = 0;
	pivot = sb_median_pivot(*a, high);
	while (sb_find_less(*a, pivot) != 0)
	{
		less = sb_find_less(*a, pivot);
		ps_a_to_b(a, b, less);
		n++;
	}
	return (n);
}

void	ps_slowsort(t_stack *a, t_stack *b, int high)
{
	int	i;
	int	pi;
	int	index;

	index = ps_bottom_index(*a, high);
	if (index <= 2)
	{
		ps_handle_three(a, b, high, index);
		return ;
	}
	i = sb_partition(a, b, high);
	ps_slowsort(a, b, a->tail->value);
	if (i-- > 0)
		ps_pipeline(PUSH_A, a, b);
	pi = a->head->value;
	while (i-- > 0)
		ps_pipeline(PUSH_A, a, b);
	ps_slowsort(a, b, pi);
}
