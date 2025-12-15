/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:06:59 by tponutha          #+#    #+#             */
/*   Updated: 2023/03/25 14:08:41 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static _Bool	sub_issame(const char *s, char c)
{
	while (*s)
	{
		if (*s != c)
			return (0);
		s++;
	}
	return (1);
}

static char	*sub_strcdup(const char *src, char c, t_mem **spt)
{
	size_t	len;
	char	*dest;

	len = ft_strclen(src, c);
	dest = lm_malloc(sizeof(char), len + 1, spt);
	if (!dest)
		return (NULL);
	(void)ft_strlcpy(dest, src, len + 1);
	return (dest);
}

static char	**box(const char *s, char c, size_t len, t_mem **spt)
{
	char	flag;
	char	**box;
	size_t	j;
	size_t	i;

	box = lm_calloc(len + 1, sizeof(char *), spt);
	j = 0;
	i = 0;
	flag = 1;
	while (s[i] && box != NULL)
	{
		if (flag && s[i] != c)
		{
			box[j] = sub_strcdup(&s[i], c, spt);
			if (!box[j])
				return (NULL);
			j += flag--;
		}
		else if (!flag && s[i] == c)
			flag = 1;
		i++;
	}
	return (box);
}

/*
This split is different from libft conterpart
- if allocation fail it just return NULL without free
- because it free thing up outside ft_split
- via stack_exit chaeck by NULL
*/

char	**ft_split(char const *s, char c, t_mem **spt)
{
	char	flag;
	size_t	len;
	size_t	i;

	if (!s || !s[0] || sub_issame(s, c))
		return (lm_calloc(1, sizeof(char *), spt));
	flag = 1;
	len = 0;
	i = 0;
	while (s[i])
	{
		if (flag && s[i] != c)
			len += flag--;
		else if (!flag && s[i] == c)
			flag = 1;
		i++;
	}
	return (box(s, c, len, spt));
}
