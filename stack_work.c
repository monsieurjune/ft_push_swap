/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:55:23 by tponutha          #+#    #+#             */
/*   Updated: 2023/04/01 01:55:21 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	stack_push(t_stack *stack, t_node *node)
{
	if (node == NULL)
		return ;
	if (stack->head == NULL)
	{
		stack->head = node;
		stack->tail = node;
	}
	else
	{
		stack->head->prev = node;
		node->next = stack->head;
		stack->head = node;
	}
	stack->n += 1;
}

t_node	*stack_pop(t_stack *stack)
{
	t_node	*node;

	if (stack->head == NULL)
		return (NULL);
	node = stack->head;
	stack->head = stack->head->next;
	if (stack->head != NULL)
		stack->head->prev = NULL;
	else
		stack->tail = NULL;
	stack->n -= 1;
	node->next = NULL;
	return (node);
}

static t_node	*stack_create_node(int value, t_mem **head)
{
	t_node	*node;

	node = lm_malloc(sizeof(t_node), 1, head);
	if (node == NULL)
		stack_exit(head);
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_stack	stack_build(int *arr, int lastpos, t_mem **head)
{
	t_stack	stack;
	t_node	*node;

	stack.head = NULL;
	stack.tail = NULL;
	stack.n = 0;
	if (arr == NULL)
		return (stack);
	while (lastpos > 0)
	{
		node = stack_create_node(arr[lastpos - 1], head);
		stack_push(&stack, node);
		lastpos--;
	}
	lm_free(arr, head);
	return (stack);
}
