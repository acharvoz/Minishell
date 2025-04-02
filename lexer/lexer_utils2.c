/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:18:44 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/01 19:29:49 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*get_token_name(t_tokens token)
{
	if (token == PIPE)
		return ("PIPE");
	if (token == GREAT)
		return ("GREAT");
	if (token == GREAT_GREAT)
		return ("GREAT_GREAT");
	if (token == LESS)
		return ("LESS");
	if (token == LESS_LESS)
		return ("LESS_LESS");
	if (token == WORD)
		return ("WORD");
	if (token == ENV_VAR)
		return ("ENV_VAR");
	return ("UNKNOWN");
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

//check si apres $ pour var env est valide ( _ ou lettre)

char	check_env_var(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$' && ((str[i + 1] == '_')
			|| (((str[i + 1] >= 65) && (str[i + 1] <= 90)))
			|| ((str[i + 1] >= 97) && (str[i + 1] <= 122))))
		return (1);
	return (0);
}

void	parsing_start(char *input, char **envp_cpy)
{
	t_lexer	*lexer_list;
	int i;

	i = 0;
	lexer_list = NULL;
	i = token_reader(input, &lexer_list, envp_cpy);
	if (i == -1)
		return ;
	print_lexer_token(lexer_list);
	call_parser(&lexer_list);
	return ;
}
