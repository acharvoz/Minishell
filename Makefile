# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 19:54:20 by acharvoz          #+#    #+#              #
#    Updated: 2025/04/02 17:18:24 by acharvoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c							\
		lexer/lexer_utils.c				\
		lexer/lexer_utils2.c			\
		lexer/quotes_handle.c			\
		lexer/token_read.c				\
		lexer/token_read_utils.c		\
		lexer/token_handle.c			\
		parser/parser_pipe.c			\
		parser/command_utils.c			\

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3
RM = rm -f

LIBFT_DIR = ../libft/
LIBFT = $(LIBFT_DIR)/libft.a

OBJS = $(SRCS:.c=.o)
INCLUDES = -I$(LIBFT_DIR) -I./includes

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re