/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:03:30 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/10 20:07:07 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//gere la gestion du mot

int	read_words(int i, char *str, t_lexer **lexer_list, char **envp_cpy)
{
	int		j;
	int		quote;
	char	*word;

	j = 0;
	quote = 0;
	while (str[i + j] && !check_oper(str[i + j]) && !is_whitespace(str[i + j]))
	{
		if (str[i + j] == 34 || str[i + j] == 39)
		{
			quote = quotes_handle(i + j, str, str[i + j]);
			if (quote == -1)
				return (-1);
			j += quote;
		}
		else
			j++;
	}
	word = ft_substr(str, i, j);
	if (!word)
		return (-1);
	word = process_word(word, envp_cpy);
	if (!add_node(word, WORD, lexer_list))
		return (-1);
	return (j);
}

//gere l'expander dans les quotes

char	*process_word(char *str, char **envp_cpy)
{
	int		i;
	bool	expand;
	char	*expanded_word;

	i = 0;
	expand = true;
	while (str[i] && str[i] != '\'' && str[i] != '\"')
		i++;
	if (str[i] == '\'')
		expand = false;
	else if (expand == true)
	{
		expanded_word = expand_env_var(str, envp_cpy);
		free(str);
		str = expanded_word;
	}
	str = remove_quotes(str);
	return (str);
}

int	token_reader(char *str, t_lexer **lexer_list, char **envp_cpy)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		i += skip_spaces(str, i);
		if (check_oper(str[i]))
			j = handle_operator(str, i, lexer_list);
		else
			j = read_words(i, str, lexer_list, envp_cpy);
		if (j <= 0)
			return (0);
		i += j;
	}
	return (1);
}
