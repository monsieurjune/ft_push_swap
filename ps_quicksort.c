/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:56:28 by tponutha          #+#    #+#             */
/*   Updated: 2023/04/06 01:34:29 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	sb_find_next_min(t_stack a, int high, long pmin)
{
	int	min;

	min = INT_MAX;
	while (1)
	{
		if (a.head->value < min && a.head->value > pmin)
		{
			min = a.head->value;
		}
		if (a.head->value == high)
			break ;
		a.head = a.head->next;
	}
	return (min);
}

// not actual median, just near (for working with 5)

static int	sb_median_pivot(t_stack a, int high)
{
	long	pmin;
	int		med;
	int		i;

	i = (ps_bottom_index(a, high) + 2) / 2;
	pmin = LONG_MIN;
	while (i > 0)
	{
		med = sb_find_next_min(a, high, pmin);
		pmin = med;
		i--;
	}
	return (med);
}

// first partiotioning
// send less than pivot away
// restore order
// return amount of node that send to b

static int	sb_partition(t_stack *a, t_stack *b, int high)
{
	int	n;
	int	less;
	int	pivot;

	n = 0;
	pivot = sb_median_pivot(*a, high);
	while (ps_find_less(*a, pivot) != 0)
	{
		less = ps_find_less(*a, pivot);
		ps_a_to_b(a, b, less);
		n++;
	}
	return (n);
}

static void	sb_sort_three(t_stack *a, t_stack *b, int high)
{
	int	i;
	int	k;

	i = ps_bottom_index(*a, sb_find_next_min(*a, high, LONG_MIN));
	if (a->n == 3)
	{
		if (i == 0)
			ps_pipeline(ROTATE_A, a, b);
		else if (i == 1)
			ps_pipeline(REV_ROTATE_A, a, b);
		if (a->head->value > a->head->next->value)
			ps_pipeline(SWAP_A, a, b);
		ps_pipeline(REV_ROTATE_A, a ,b);
		return ;
	}
	k = i;
	while (i-- > 0)
		ps_pipeline(PUSH_B, a, b);
	ps_pipeline(ROTATE_A, a, b);
	while (k-- > 0)
		ps_pipeline(PUSH_A, a, b);
	if (a->head->value > a->head->next->value)
		ps_pipeline(SWAP_A, a, b);
	ps_pipeline(REV_ROTATE_A, a, b);
}

// top always head
// but bottom we can't assume it
// since we know how much we throw at b
// and we don't rotate b
// we can safely throw it back
// even it not, we still partition and sort it  

void	ps_quicksort(t_stack *a, t_stack *b, int high)
{
	int	i;
	int	pi;

	if (ps_bottom_index(*a, high) <= 0)
		return ;
    if (ps_bottom_index(*a, high) == 1)
    {
		if (a->head->value > high)
			ps_pipeline(SWAP_A, a, b);
		return ;
    }
	if (ps_bottom_index(*a, high) == 2)
	{
		sb_sort_three(a, b, high);
		return ;
	}
	i = sb_partition(a, b, high);
	ps_quicksort(a, b, a->tail->value);
	if (i-- > 0)
		ps_pipeline(PUSH_A, a, b);
	pi = a->head->value;
	while (i-- > 0)
		ps_pipeline(PUSH_A, a, b);
	ps_quicksort(a, b, pi);
}

/*
#include <stdio.h>
#include <string.h>
void test_print(t_stack a, t_stack b)
{
	t_node	*runa = a.head;
	t_node	*runb = b.head;

	printf("a	b\n");
	while (runa != NULL || runb != NULL)
	{
		if (runa != NULL)
		{
			printf("%d	", runa->value);
			runa = runa->next;
		}
		else
			printf("_	");
		if (runb != NULL)
		{
			printf("%d\n", runb->value);
			runb = runb->next;
		}
		else
			printf("_\n");
	}
	printf("\n-------------------\n");
}

int main(int ac, char **av)
{
	int i = 1;
	t_mem	*head = NULL;
	int *arr = lm_malloc(sizeof(int), ac - 1, &head);
	while (i < ac)
	{
		arr[i - 1] = atoi(av[i]);
		i++;
	}
	t_stack a = stack_build(arr, ac - 1, &head);
	t_stack b = stack_build(NULL, 0, &head);
	char read[10];
	test_print(a, b);
	while (1)
	{
		scanf("%s", read);
		if (strcmp("E", read) == 0)
			break;
		int high = atoi(read);
		int med = sb_median_pivot(a, high);
		test_print(a, b);
		printf("MED : %d\n", med);
	}
	lm_flush(&head);
}
*/
// There is Bug

// 1 2 3 OK_while
// 1 3 2 OK_while OK_3
// 2 1 3 OK_while OK_3
// 2 3 1 OK_while OK_3
// 3 1 2 OK_while OK_3
// 3 2 1 OK_while OK_3