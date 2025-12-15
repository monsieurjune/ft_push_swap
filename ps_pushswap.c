/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_pushswap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:32:41 by tponutha          #+#    #+#             */
/*   Updated: 2025/12/16 00:43:46 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

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
	pivot = ps_median_pivot(*a, high);
	while (sb_find_less(*a, pivot) != 0)
	{
		less = sb_find_less(*a, pivot);
		ps_a_to_b(a, b, less);
		n++;
	}
	return (n);
}

void	sb_slowsort(t_stack *a, t_stack *b, int high)
{
	int	i;
	int	pi;
	int	index;

	index = ps_bottom_index(*a, high);
	if (index <= 2)
	{
		ps_sort_three(a, b, high);
		return ;
	}
	i = sb_partition(a, b, high);
	sb_slowsort(a, b, a->tail->value);
	if (i-- > 0)
		ps_pipeline(PUSH_A, a, b);
	pi = a->head->value;
	while (i-- > 0)
		ps_pipeline(PUSH_A, a, b);
	sb_slowsort(a, b, pi);
}

static int	sb_issorted(int *arr, int len)
{
	int	i;

	i = 1;
	if (len == 1)
		return (TRUE);
	while (i < len)
	{
		if (arr[i] < arr[i - 1])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_mem		*ps_mem;
	t_stack		a;
	t_stack		b;
	int			*arr;
	int			len;

	if (ac <= 1)
		return (0);
	arr = stack_check_n_return(ac, &len, av, &ps_mem);
	if (!sb_issorted(arr, len))
	{
		a = stack_build(arr, len, &ps_mem);
		b = stack_build(NULL, 0, &ps_mem);
		lm_free(arr, &ps_mem);
		if (a.n < 10)
			sb_slowsort(&a, &b, a.tail->value);
		else
			ps_moresort(&a, &b, a.tail->value);
	}
	lm_flush(&ps_mem);
	return (0);
}
