/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 08:57:22 by tponutha          #+#    #+#             */
/*   Updated: 2025/12/16 00:44:29 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include <stdio.h>

// size = all_argv_len + (ac - 1) + 1
// size = all_argv_len + ac

static size_t	sb_argvlen(int ac, char **av)
{
	size_t	size;
	int		i;

	i = 1;
	size = 0;
	while (i < ac)
	{
		size += ft_strclen(av[i], 0);
		i++;
	}
	return (size + ac);
}

/* Transform av to single string
-> str[n] = str[n-1] + av[n] + ' '
-> alloc once then copy later
*/

static char	*sb_str_transform(int ac, char **av, t_mem **spt)
{
	char	*str;
	int		i;
	size_t	size;

	i = 1;
	size = sb_argvlen(ac, av);
	str = lm_malloc(sizeof(char), size, spt);
	if (str == NULL)
		stack_exit(spt);
	str[0] = 0;
	while (i < ac)
	{
		str = ft_strncat(str, av[i], size);
		str = ft_strncat(str, " ", size);
		i++;
	}
	return (str);
}

/* Transform array of string to array of int
Using stack_atol to give value
- if right format then give long (convert to int later)
- if wrong format then give LONG_MIN
	- if got (LONG_MIN) then call stack_exit
*/

static int	*sb_intarr(char **box, int len, t_mem **spt, t_mem **head)
{
	long	temp;
	int		i;
	int		*arr;

	i = 0;
	arr = lm_malloc(sizeof(int), len, head);
	if (arr == NULL)
	{
		lm_flush(head);
		stack_exit(spt);
	}
	while (i < len)
	{
		temp = stack_atoi(box[i]);
		if (temp == LONG_MIN)
		{
			lm_flush(head);
			stack_exit(spt);
		}
		arr[i] = (int)temp;
		i++;
	}
	return (arr);
}

/* check if args are in correct
- correct -> return int array
- correct but sorted -> retrun NULL
- not correct -> call stack_exit
- allocation fail -> call stack_exit
- head always NULL so handle after malloced int array
*/

int	*stack_check_n_return(int ac, int *len, char **av, t_mem **head)
{
	t_mem		*spt;
	char		**box;
	char		*str;
	int			*arr;

	spt = NULL;
	*head = NULL;
	*len = 0;
	str = sb_str_transform(ac, av, &spt);
	box = ft_split(str, ' ', &spt);
	if (box == NULL)
		stack_exit(&spt);
	while (box[*len] != 0)
		(*len)++;
	arr = sb_intarr(box, *len, &spt, head);
	lm_flush(&spt);
	if (stack_isduplicate(arr, *len, head))
		stack_exit(head);
	return (arr);
}
