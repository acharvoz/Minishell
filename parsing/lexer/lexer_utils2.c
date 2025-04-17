/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:18:44 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/17 12:47:00 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	return ("UNKNOWN");
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

void	parsing_start(char *input, char **envp_cpy)
{
	t_lexer	*lexer_list;
	int		i;

	i = 0;
	lexer_list = NULL;
	i = token_reader(input, &lexer_list, envp_cpy);
	if (i <= 0)
		return ;
	print_lexer_token(lexer_list);
	call_parser(&lexer_list);
	return ;
}

char	*ft_strjoin_char(char *s, char c)
{
	char	*new_str;
	int		len;
	int		i;

	if (!s)
		len = 0;
	else
		len = ft_strlen(s);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	return (new_str);
}
