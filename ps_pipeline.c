/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:46:43 by tponutha          #+#    #+#             */
/*   Updated: 2025/12/16 00:43:41 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	ps_print_cmd(int cmd)
{
	if (cmd == SWAP_A)
		write(1, STR_SWAP_A, sizeof(STR_SWAP_A) - 1);
	else if (cmd == SWAP_B)
		write(1, STR_SWAP_B, sizeof(STR_SWAP_B) - 1);
	else if (cmd == SWAP_AB)
		write(1, STR_SWAP_AB, sizeof(STR_SWAP_AB) - 1);
	else if (cmd == PUSH_A)
		write(1, STR_PUSH_A, sizeof(STR_PUSH_A) - 1);
	else if (cmd == PUSH_B)
		write(1, STR_PUSH_B, sizeof(STR_PUSH_B) - 1);
	else if (cmd == ROTATE_A)
		write(1, STR_ROTATE_A, sizeof(STR_ROTATE_A) - 1);
	else if (cmd == ROTATE_B)
		write(1, STR_ROTATE_B, sizeof(STR_ROTATE_B) - 1);
	else if (cmd == ROTATE_AB)
		write(1, STR_ROTATE_AB, sizeof(STR_ROTATE_AB) - 1);
	else if (cmd == REV_ROTATE_A)
		write(1, STR_REV_ROTATE_A, sizeof(STR_REV_ROTATE_A) - 1);
	else if (cmd == REV_ROTATE_B)
		write(1, STR_REV_ROTATE_B, sizeof(STR_REV_ROTATE_B) - 1);
	else if (cmd == REV_ROTATE_AB)
		write(1, STR_REV_ROTATE_AB, sizeof(STR_REV_ROTATE_AB) - 1);
	write(1, "\n", 1);
}

static void	ps_do_both(int cmd, t_stack *a, t_stack *b)
{
	if (cmd == SWAP_AB)
	{
		stack_swap(a);
		stack_swap(b);
	}
	else if (cmd == ROTATE_AB)
	{
		stack_rotate(a);
		stack_rotate(b);
	}
	else if (cmd == REV_ROTATE_AB)
	{
		stack_reverse_rotate(a);
		stack_reverse_rotate(b);
	}
}

void	ps_pipeline(int cmd, t_stack *a, t_stack *b)
{
	if (cmd == SWAP_A)
		stack_swap(a);
	else if (cmd == SWAP_B)
		stack_swap(b);
	else if (cmd == PUSH_A)
		stack_pop_push(a, b);
	else if (cmd == PUSH_B)
		stack_pop_push(b, a);
	else if (cmd == ROTATE_A)
		stack_rotate(a);
	else if (cmd == ROTATE_B)
		stack_rotate(b);
	else if (cmd == REV_ROTATE_A)
		stack_reverse_rotate(a);
	else if (cmd == REV_ROTATE_B)
		stack_reverse_rotate(b);
	else
		ps_do_both(cmd, a, b);
	ps_print_cmd(cmd);
}

void	ps_a_to_b(t_stack *a, t_stack *b, int i)
{
	if (i > 0)
	{
		while (i > 1)
		{
			ps_pipeline(ROTATE_A, a, b);
			i--;
		}
		ps_pipeline(PUSH_B, a, b);
	}
	else if (i < 0)
	{
		while (i <= -1)
		{
			ps_pipeline(REV_ROTATE_A, a, b);
			i++;
		}
		ps_pipeline(PUSH_B, a, b);
	}
}
