/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listmem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:47:56 by tponutha          #+#    #+#             */
/*   Updated: 2025/12/15 23:35:34 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listmem.h"

// if alloc node fail then free mem

static t_mem	*lm_create_node(void *mem)
{
	t_mem	*node;

	node = malloc(sizeof(t_mem));
	if (node == NULL)
	{
		free(mem);
		return (NULL);
	}
	node->mem = mem;
	node->next = NULL;
	return (node);
}

static void	lm_insert_node(t_mem **head, t_mem *node)
{
	t_mem	*oldhead;

	if (node == NULL)
		return ;
	oldhead = *head;
	*head = node;
	(*head)->next = oldhead;
}

void	*lm_malloc(size_t byte, size_t n, t_mem **head)
{
	t_mem		*node;
	void		*mem;

	if (byte == SIZE_MAX || n == SIZE_MAX)
		return (NULL);
	mem = malloc(byte * n);
	if (mem == NULL)
		return (NULL);
	node = lm_create_node(mem);
	if (node == NULL)
		return (NULL);
	lm_insert_node(head, node);
	return (mem);
}

static void	*ft_memset(void *ptr, int c, size_t byte)
{
	size_t	i;

	if (!ptr)
		return (NULL);
	i = 0;
	while (i < byte)
	{
		((unsigned char *)ptr)[i] = ((unsigned char *)&c)[0];
		i++;
	}
	return (ptr);
}

void	*lm_calloc(size_t byte, size_t n, t_mem **head)
{
	t_mem		*node;
	void		*mem;

	if (byte == SIZE_MAX || n == SIZE_MAX)
		return (NULL);
	byte *= n;
	mem = malloc(byte);
	if (mem == NULL)
		return (NULL);
	node = lm_create_node(mem);
	if (node == NULL)
		return (NULL);
	lm_insert_node(head, node);
	return (ft_memset(mem, 0, byte));
}
