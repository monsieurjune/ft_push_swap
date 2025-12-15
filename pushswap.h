/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:35:46 by tponutha          #+#    #+#             */
/*   Updated: 2023/04/10 00:27:34 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "stack.h"
#include <stdio.h>

// ps_pipeline.c
void	ps_pipeline(int cmd, t_stack *a, t_stack *b);
void	ps_a_to_b(t_stack *a, t_stack *b, int i);

// ps_
void	ps_moresort(t_stack *a, t_stack *b, int high);

void	ps_lesssort(t_stack *a, t_stack *b, int high);

// ps_utility.c
int     ps_bottom_index(t_stack a, int bottom);
void	ps_handle_three(t_stack *a, t_stack *b, int high, int index);
int	    ps_median_pivot(t_stack a, int high);
void	ps_sort_three(t_stack *a, t_stack *b, int high);


#endif