# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 19:54:20 by acharvoz          #+#    #+#              #
#    Updated: 2025/01/06 20:00:27 by acharvoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	../printf/ft_printf.c			\
		../printf/ft_print_char.c		\
		../printf/ft_print_hexa.c		\
		../printf/ft_print_nbr.c		\
		../printf/ft_print_prct.c		\
		../printf/ft_print_ptr.c		\
		../printf/ft_print_str.c		\
		../printf/ft_print_unsigned.c	\
		

CC = cc
RM = rm -f
FLAGS = -Wall -Werror -Wextra 
NAME = minishell
OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
