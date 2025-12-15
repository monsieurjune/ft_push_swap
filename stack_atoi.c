/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:17:06 by tponutha          #+#    #+#             */
/*   Updated: 2023/04/01 07:21:43 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

/* 	This function use to initialize value
	And check format of string 
	- if correct => 0
	- if wrong => LONG_MIN
*/

static long	sb_format_check(char *str)
{
	if (str == NULL)
		return (LONG_MIN);
	str += (*str == '+' || *str == '-');
	if (*str == 0)
		return (LONG_MIN);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (LONG_MIN);
		str++;
	}
	return (0);
}

/* this atol is different from normal aotl
1.) it doesn't like anything beside number & spacebar
2.) since (spacebar) is gone due to ft_split
3.) so it only likes numbers
4.) if thrown anything that isn't number, it will give LONG_MIN
- if correct => [INT_MIN, INT_MAX]
- if wrong => LONG_MIN
*/

long	stack_atoi(char *str)
{
	int		i;
	long	sum;
	long	neg;

	i = 0;
	neg = 1;
	sum = sb_format_check(str);
	if (sum == LONG_MIN)
		return (LONG_MIN);
	if (str[i] == '-')
		neg = -1;
	i += (str[i] == '+' || str[i] == '-');
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + (str[i] - '0');
		if (neg * sum < INT_MIN || neg * sum > INT_MAX)
			return (LONG_MIN);
		i++;
	}
	return (neg * sum);
}
