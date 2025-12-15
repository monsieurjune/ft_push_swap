# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/29 03:48:25 by tponutha          #+#    #+#              #
#    Updated: 2023/04/10 00:23:02 by tponutha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Main properties
NAME		= push_swap
TESTER_PATH	= ./push_swap_tester

# Complier & shell thing
COM		= cc
RM		= rm -f
CFLAG	= -Wall -Werror -Wextra

# Listmem Directory
MEM_DIR		= ./
MEM_FILE	= listfree.c listmem.c
MEM_SRCS	= $(addprefix $(MEM_DIR), $(MEM_FILE))

# Stack Directory
STACK_DIR	= ./
STACK_FILE	= stack_args.c stack_atoi.c stack_command.c stack_duplicate.c \
				stack_split.c stack_utility.c stack_work.c
STACK_SRCS	= $(addprefix $(STACK_DIR), $(STACK_FILE))

# Main Directory
MAIN_DIR	= ./
MAIN_FILE	= ps_utility.c ps_pipeline.c ps_pushswap.c ps_lesssort.c \
				ps_moresort.c
MAIN_SRCS	= $(addprefix $(MAIN_DIR), $(MAIN_FILE))

# Complie Process
SRCS	= $(MAIN_SRCS) $(MEM_SRCS) $(STACK_SRCS)
OBJ		= $(SRCS:.c=.o)
IFLAG	= -I$(MAIN_DIR)
.c.o:
	$(COM) $(CFLAG) -c $(IFLAG) $< -o $(<:.c=.o)

# MAIN RULES
$(NAME):	$(OBJ)
	$(COM) $(CFLAG) $(OBJ) -o $(NAME)

all:	$(NAME)

bonus:	$(NAME)

debug:	$(OBJ)
	@$(COM) $(CFLAG) -g $(SRCS) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean:	clean
	@$(RM) $(NAME)

dclean: fclean
	@$(RM) -r push_swap.dSYM

re:	fclean all

# ETC RULES
norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS)

.PHONY: all clean fclean re bonus test clone