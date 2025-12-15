/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:53:41 by tponutha          #+#    #+#             */
/*   Updated: 2025/12/16 00:44:56 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include <unistd.h>
# include <limits.h>
# include "listmem.h"

# define TRUE 1
# define FALSE 0

// Define Variables
# define SWAP_A 1
# define SWAP_B 2
# define SWAP_AB 3
# define PUSH_A 4
# define PUSH_B 5
# define ROTATE_A 6
# define ROTATE_B 7
# define ROTATE_AB 8
# define REV_ROTATE_A 9
# define REV_ROTATE_B 10
# define REV_ROTATE_AB 11

// Define String
# define STR_SWAP_A "sa"
# define STR_SWAP_B "sb"
# define STR_SWAP_AB "ss"
# define STR_PUSH_A "pa"
# define STR_PUSH_B "pb"
# define STR_ROTATE_A "ra"
# define STR_ROTATE_B "rb"
# define STR_ROTATE_AB  "rr"
# define STR_REV_ROTATE_A "rra"
# define STR_REV_ROTATE_B "rrb"
# define STR_REV_ROTATE_AB "rrr"

// Define node of stack
typedef struct s_node
{
	int				value;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

// Define main part of stack
typedef struct s_stack
{
	struct s_node	*head;
	struct s_node	*tail;
	int				n;
}	t_stack;

// stack_work.c
t_stack	stack_build(int *arr, int lastpos, t_mem **head);
t_node	*stack_pop(t_stack *stack);
void	stack_push(t_stack *stack, t_node *node);

// stack_command.c
void	stack_swap(t_stack *stack);
void	stack_pop_push(t_stack *dest, t_stack *src);
void	stack_rotate(t_stack *stack);
void	stack_reverse_rotate(t_stack *stack);
void	stack_exit(t_mem **head);

// stack_split.c
char	**ft_split(char const *s, char c, t_mem **spt);

// stack_atoi.c
long	stack_atoi(char *str);

// stack_duplicate.c
int		stack_isduplicate(int *arr, int size, t_mem **head);

// stack_args.c
int		*stack_check_n_return(int ac, int *len, char **av, t_mem **head);

// stack_utility.c
void	*ft_memmove(void *dst, const void *src, size_t byte);
size_t	ft_strclen(const char *str, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strncat(char *dst, const char *src, size_t size);

#endif
