/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_radixsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:36:27 by tponutha          #+#    #+#             */
/*   Updated: 2025/12/15 23:48:14 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	sb_bucket_ones(t_stack *a, t_stack *b, int num)
{
	int		n;
	t_node	*run;

	n = a->n;
	run = a->head;
	while (n > 0)
	{
		if ((num & a->head->value) == 0)
			ps_pipeline(PUSH_B, a, b);
		else
			ps_pipeline(ROTATE_A, a, b);
		n--;
	}
	while (b->head != NULL)
		ps_pipeline(PUSH_A, a, b);
}

void	ps_radixsort(t_stack *a, t_stack *b)
{
	t_node	*run;
	int		digit;
	int		max_digit;
	int		check;

	run = a->head;
	max_digit = 0;
	while (run != NULL && max_digit < 30)
	{
		check = 30;
		while ((1 << check & run->value) == 0 && check >= 0)
			check--;
		if (max_digit < check)
			max_digit = check;
		run = run->next;
	}
	digit = 0;
	while (digit <= max_digit)
	{
		sb_bucket_ones(a, b, 1 << digit);
		digit++;
	}
}
