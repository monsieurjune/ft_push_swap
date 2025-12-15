/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_duplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 03:39:22 by tponutha          #+#    #+#             */
/*   Updated: 2025/12/15 23:44:42 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	sb_intswap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	*sb_clone_arr(int *arr, int size, t_mem **head)
{
	int	*clone;

	clone = lm_malloc(sizeof(int), size, head);
	if (clone == NULL)
		return (NULL);
	return (ft_memmove(clone, arr, sizeof(int) * size));
}

static int	sb_first_partition(int *arr, int low, int high)
{
	int	i;
	int	j;
	int	pivot;

	pivot = arr[low];
	i = low;
	j = low + 1;
	while (j <= high)
	{
		if (arr[j] < pivot)
		{
			i++;
			sb_intswap(&arr[i], &arr[j]);
		}
		j++;
	}
	sb_intswap(&arr[i], &arr[low]);
	return (i);
}

static void	sb_quicksort(int *arr, int low, int high)
{
	int	pi;

	if (low >= high)
		return ;
	pi = sb_first_partition(arr, low, high);
	sb_quicksort(arr, low, pi - 1);
	sb_quicksort(arr, pi + 1, high);
}

int	*stack_isduplicate(int *arr, int size, t_mem **head)
{
	int	i;
	int	*copy;

	i = 1;
	copy = sb_clone_arr(arr, size, head);
	if (copy == NULL)
		stack_exit(head);
	sb_quicksort(copy, 0, size - 1);
	while (i < size)
	{
		if (copy[i] == copy[i - 1])
			return (NULL);
		i++;
	}
	return (copy);
}
