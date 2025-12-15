/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_pushswap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:32:41 by tponutha          #+#    #+#             */
/*   Updated: 2025/12/15 23:37:16 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

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

static int	*sb_index(int *arr, int *copy, int len, t_mem **head)
{
	int	current;
	int	actual;
	int	*index;

	index = lm_malloc(sizeof(int), len, head);
	if (index == NULL)
		stack_exit(head);
	current = 0;
	while (current < len)
	{
		actual = 0;
		while (actual < len)
		{
			if (arr[current] == copy[actual])
			{
				index[current] = actual;
				break ;
			}
			actual++;
		}
		current++;
	}
	return (index);
}

static int	sb_init(int	**arr, int len, t_mem **head)
{
	int	*copy;
	int	*index;

	copy = stack_isduplicate(*arr, len, head);
	if (copy == NULL)
		stack_exit(head);
	if (sb_issorted(*arr, len))
		return (FALSE);
	index = sb_index(*arr, copy, len, head);
	lm_free(copy, head);
	lm_free(arr, head);
	*arr = index;
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
	if (sb_init(&arr, len, &ps_mem))
	{
		a = stack_build(arr, len, &ps_mem);
		b = stack_build(NULL, 0, &ps_mem);
		lm_free(arr, &ps_mem);
		if (a.n < 10)
			ps_slowsort(&a, &b, a.tail->value);
		else
			ps_radixsort(&a, &b);
	}
	lm_flush(&ps_mem);
	return (0);
}
