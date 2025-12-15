/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_moresort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:27:06 by tponutha          #+#    #+#             */
/*   Updated: 2025/12/15 23:36:44 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	sb_less_amount(t_stack a, int pivot, int high, int *min)
{
	int	m;

	m = 0;
	*min = INT_MAX;
	while (1)
	{
		if (a.head->value < pivot)
		{
			if (a.head->value < *min)
				*min = a.head->value;
			m++;
		}
		if (a.head->value == high)
			break ;
		a.head = a.head->next;
	}
	return (m);
}

static int	sb_more_part(t_stack *a, t_stack *b, int high, int *min)
{
	_Bool	isfirst;
	int		n;
	int		k;
	int		first;
	int		pivot;

	k = 0;
	isfirst = TRUE;
	pivot = ps_median_pivot(*a, high);
	n = sb_less_amount(*a, pivot, high, min);
	while (n > 0)
	{
		n -= a->head->value < pivot;
		k += a->head->value >= pivot;
		if (a->head->value < pivot && isfirst)
		{
			isfirst = FALSE;
			first = a->head->value;
		}
		if (a->head->value < pivot)
			ps_pipeline(PUSH_B, a, b);
		else
			ps_pipeline(ROTATE_A, a, b);
	}
	while (k-- > 0)
		ps_pipeline(REV_ROTATE_A, a, b);
	return (first);
}

void	ps_moresort(t_stack *a, t_stack *b, int high)
{
	int	min;
	int	first;
	int	index;

	index = ps_bottom_index(*a, high);
	//test_print(a->head, b->head);
	if (index <= 2)
	{
		ps_handle_three(a, b, high, index);
		return ;
	}
	first = sb_more_part(a, b, high, &min);
	ps_moresort(a, b, a->tail->value);
	ps_lesssort(a, b, first);
}
