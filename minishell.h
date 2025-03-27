/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:52:30 by acharvoz          #+#    #+#             */
/*   Updated: 2025/03/27 16:21:28 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//norminette *.c | norminette lexer/*.c

# include "../libft/libft.h"
# include "../printf/printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef enum s_tokens
{
	PIPE = 1,
	GREAT = 2,
	GREAT_GREAT = 3,
	LESS = 4,
	LESS_LESS = 5,
	WORD = 6, 
	ENV_VAR = 7,
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	char			*history;
	t_tokens			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_simple_cmds
{
	char					**str;
	//int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}		t_simple_cmds;

typedef struct s_tools
{

}	t_tools;

//												LEXER											//

int	token_reader(char *str, t_lexer **lexer_list, char **envp_cpy);
int	handle_operator(char *str, int i, t_lexer **lexer_list);
t_tokens	check_oper(int c);
int	quotes_handle(int i, char *str, char del);
int	is_whitespace(char c);
t_lexer	*ft_lexer_new(char *str, int token);
void	ft_lexer_add_back(t_lexer **lst, t_lexer *new);
int	read_words(int i, char *str, t_lexer **lexer_list, char **envp_cpy);
int	add_node(char *str, t_tokens token, t_lexer **lexer_list);
int	skip_spaces(char *str, int i);
void print_lexer_token(t_lexer *lexer_list);
const char *get_token_name(t_tokens token);
char check_env_var(char *str);
int	handle_var_env(char *str, int i, t_lexer **lexer_list, char **envp_cpy);
char **ft_strcpy_envp(char **envp);
char *change_var_env(char **envp_cpy, char *var_env);
void	parsing_start(char *input, char **envp_cpy);
char	*expand_env_var2(char *str, int *i, char **envp_cpy, char *result);
char	*expand_env_var(char *str, char **envp_cpy);
char	*ft_strjoin_char(char *s, char c);

//------------------------------------------PARSER------------------------------------------//

void	call_parser(t_lexer **lexer_list);
t_simple_cmds	*build_cmd_list(t_lexer **lexer_list);
t_simple_cmds	*section_pipe(t_lexer **lexer_list);
void	add_token_to_cmd(t_simple_cmds *cmd, t_lexer *tmp);
t_simple_cmds	*init_simple_cmd(void);
char *remove_quotes(char *str);

//------------------------------------------TESTS------------------------------------------//

void	print_cmd(t_simple_cmds *cmd);

#endif