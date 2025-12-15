/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:36:47 by tponutha          #+#    #+#             */
/*   Updated: 2023/04/10 13:04:23 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int ps_bottom_index(t_stack a, int bottom)
{
    int	i;

	i = 0;
	if (a.head == NULL)
		return (-1);
	while (a.head != a.tail && a.head->prev != a.tail)
	{
		if (a.head->value == bottom)
			return (i);
		a.head = a.head->next;
		if (a.tail->value == bottom)
			return (a.n - i - 1);
		a.tail = a.tail->prev;
		i++;
	}
	if (a.head->value == bottom)
		return (i);
	return (-1);
}

void	ps_handle_three(t_stack *a, t_stack *b, int high, int index)
{
	if (index <= 0)
		return ;
    if (index == 1)
    {
		if (a->head->value > high)
			ps_pipeline(SWAP_A, a, b);
		return ;
    }
	if (index == 2)
		return (void)ps_sort_three(a, b, high);
}

static int	sb_find_next_min(t_stack a, int high, long pmin)
{
	int	min;

	min = INT_MAX;
	while (1)
	{
		if (a.head->value < min && a.head->value > pmin)
			min = a.head->value;
		if (a.head->value == high)
			break ;
		a.head = a.head->next;
	}
	return (min);
}

int	ps_median_pivot(t_stack a, int high)
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

void	ps_sort_three(t_stack *a, t_stack *b, int high)
{
	int	i;
	int	k;

	i = ps_bottom_index(*a, sb_find_next_min(*a, high, LONG_MIN));
	if (a->n == 3)
	{
		if (i == 0)
			ps_pipeline(ROTATE_A, a, b);
		else if (i == 1)
			ps_pipeline(REV_ROTATE_A, a, b);
		if (a->head->value > a->head->next->value)
			ps_pipeline(SWAP_A, a, b);
		return (void)ps_pipeline(REV_ROTATE_A, a ,b);
	}
	k = i;
	while (i-- > 0)
		ps_pipeline(PUSH_B, a, b);
	ps_pipeline(ROTATE_A, a, b);
	while (k-- > 0)
		ps_pipeline(PUSH_A, a, b);
	if (a->head->value > a->head->next->value)
		ps_pipeline(SWAP_A, a, b);
	ps_pipeline(REV_ROTATE_A, a, b);
}