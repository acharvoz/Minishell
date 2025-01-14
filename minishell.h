/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:52:30 by acharvoz          #+#    #+#             */
/*   Updated: 2025/01/14 06:41:26 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../printf/printf.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

//																				LEXER															//


typedef struct s_lexer
{
	char			*str;
	t_token		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef enum s_tokens
{
	PIPE = 1,
	GREAT = 2,
	GREAT_GREAT = 3,
	LESS = 4,
	LESS_LESS = 5,
}	t_tokens;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_tools
{

}	t_tools;

#endif