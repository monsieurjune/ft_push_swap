/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_lesssort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:26:41 by tponutha          #+#    #+#             */
/*   Updated: 2025/12/15 23:36:35 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	sb_sort_three_less(t_stack *a, t_stack *b)
{
	int	newhigh;

	newhigh = b->head->value;
	ps_pipeline(PUSH_A, a, b);
	ps_pipeline(PUSH_A, a, b);
	ps_pipeline(PUSH_A, a, b);
	ps_sort_three(a, b, newhigh);
}

static int	sb_more_amount(t_stack b, int pivot, int high, int *max)
{
	int	m;

	m = 0;
	*max = INT_MIN;
	while (1)
	{
		if (b.head->value > pivot)
		{
			if (b.head->value > pivot)
				*max = b.head->value;
			m++;
		}
		if (b.head->value == high)
			break;
		b.head = b.head->next;
	}
	return (m);
}

static int	sb_less_part(t_stack *a, t_stack *b, int high, int *max)
{
	_Bool	isfirst;
	int		n;
	int		k;
	int		first;
	int		pivot;

	k = 0;
	isfirst = TRUE;
	pivot = ps_median_pivot(*b, high);
	n = sb_more_amount(*b, pivot, high, max);
	while (n > 0)
	{
		n -= b->head->value > pivot;
		k += b->head->value <= pivot;
		if (b->head->value > pivot && isfirst)
		{
			isfirst = FALSE;
			first = b->head->value;
		}
		if (b->head->value > pivot)
			ps_pipeline(PUSH_A, a, b);
		else
			ps_pipeline(ROTATE_B, a, b);
	}
	while (k-- > 0)
		ps_pipeline(REV_ROTATE_B, a, b);
	return (first);
}

void	ps_lesssort(t_stack *a, t_stack *b, int high)
{
	int	max;
	int	first;
	int	index;

	index = ps_bottom_index(*b, high);
	if (index < 0)
		return ;
	if (index == 0)
		return ((void)ps_pipeline(PUSH_A, a, b));
	else if (index == 1)
	{
		if (b->head->value < high)
			ps_pipeline(SWAP_B, a, b);
		ps_pipeline(PUSH_A, a, b);
		ps_pipeline(PUSH_A, a, b);
		return ;
	}
	else if (index == 2)
	{
		sb_sort_three_less(a, b);
		return ;
	}
	first = sb_less_part(a, b, high, &max);
	ps_moresort(a, b, first);
	ps_lesssort(a, b, b->tail->value);
}
