/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:52:30 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/17 14:43:43 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//norminette *.c | norminette lexer/*.c

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <signal.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../printf/printf.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef enum s_tokens
{
	PIPE = 1,
	GREAT = 2,
	GREAT_GREAT = 3,
	LESS = 4,
	LESS_LESS = 5,
	WORD = 6,
}	t_tokens;

typedef struct s_lexer
{
	int				i;
	char			*str;
	char			*history;
	struct s_lexer	*next;
	struct s_lexer	*prev;
	t_tokens		token;
}	t_lexer;

typedef struct s_simple_cmds
{
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
	char					**str;
	char					*hd_file_name;
	int						num_redirections;
	t_lexer					*redirections;
}	t_simple_cmds;

//-----------------------------------PARSER-------------------------------//

t_tokens		check_oper(int c);
t_lexer			*ft_lexer_new(char *str, int token);
t_simple_cmds	*init_simple_cmd(void);
t_simple_cmds	*section_pipe(t_lexer **lexer_list);
t_simple_cmds	*build_cmd_list(t_lexer **lexer_list);
int				is_whitespace(char c);
int				skip_spaces(char *str, int i);
int				quotes_handle(int i, char *str, char del);
int				handle_operator(char *str, int i, t_lexer **lexer_list);
int				add_node(char *str, t_tokens token, t_lexer **lexer_list);
int				token_reader(char *str, t_lexer **lexer_list, char **envp_cpy);
int				read_words(int i, char *str, t_lexer **lx_lst, char **envp_cpy);
char			*remove_quotes(char *str);
char			**ft_strcpy_envp(char **envp);
char			*ft_strjoin_char(char *s, char c);
char			*process_word(char *str, char **envp_cpy);
char			*change_var_env(char **envp_cpy, char *var_env);
char			*expand_env_var(char *str, char **envp_cpy, int i);
char			*expand_env_var2(char *str, int *i, char **envp_cpy, char *rst);
const char		*get_token_name(t_tokens token);
void			handle_sigint(int sig);
void			call_parser(t_lexer **lexer_list);
void			print_lexer_token(t_lexer *lexer_list);
void			ft_lexer_add_back(t_lexer **lst, t_lexer *new);
void			parsing_start(char *input, char **envp_cpy);
void			add_token_to_cmd(t_simple_cmds *cmd, t_lexer *tmp);
bool			should_expand_var(char *str);

//----------------------------------TESTS-----------------------------------//

void			print_cmd(t_simple_cmds *cmd);

#endif