/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:57:23 by tponutha          #+#    #+#             */
/*   Updated: 2023/04/01 01:29:24 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	stack_swap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (stack->head == stack->tail)
		return ;
	first = stack_pop(stack);
	second = stack_pop(stack);
	stack_push(stack, first);
	stack_push(stack, second);
}

void	stack_pop_push(t_stack *dest, t_stack *src)
{
	t_node	*node;

	if (src->head == NULL)
		return ;
	node = stack_pop(src);
	stack_push(dest, node);
}

void	stack_rotate(t_stack *stack)
{
	t_node	*node;

	if (stack->head == stack->tail)
		return ;
	node = stack_pop(stack);
	stack->tail->next = node;
	node->prev = stack->tail;
	stack->tail = node;
	stack->n += 1;
}

void	stack_reverse_rotate(t_stack *stack)
{
	t_node	*node;
	t_node	*almost_last;

	if (stack->head == stack->tail)
		return ;
	node = stack->tail;
	almost_last = stack->tail->prev;
	almost_last->next = NULL;
	node->prev = NULL;
	stack->tail = almost_last;
	stack->n -= 1;
	stack_push(stack, node);
}

void	stack_exit(t_mem **head)
{
	lm_flush(head);
	write(2, "Error\n", 6);
	exit(EXIT_SUCCESS);
}
