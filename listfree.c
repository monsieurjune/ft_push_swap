/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:23:44 by tponutha          #+#    #+#             */
/*   Updated: 2023/03/18 18:00:19 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listmem.h"

static void	lm_free_node(t_mem **head, t_mem *node, t_mem *prev)
{
	if (prev == NULL)
		*head = (*head)->next;
	else
		prev->next = node->next;
	free(node->mem);
	free(node);
}

void	lm_free(void *byte, t_mem **head)
{
	t_mem	*runner;
	t_mem	*prev;

	prev = NULL;
	runner = *head;
	while (runner != NULL)
	{
		if (runner->mem == byte)
		{
			lm_free_node(head, runner, prev);
			return ;
		}
		prev = runner;
		runner = runner->next;
	}
}

void	lm_flush(t_mem **head)
{
	t_mem	*front;

	if (*head == NULL )
		return ;
	while (*head != NULL)
	{
		front = (*head)->next;
		free((*head)->mem);
		free(*head);
		*head = front;
	}
}
