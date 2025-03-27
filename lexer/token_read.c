/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:03:30 by acharvoz          #+#    #+#             */
/*   Updated: 2025/03/27 16:26:57 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_words(int i, char *str, t_lexer **lexer_list, char **envp_cpy)
{
	int		j;
	int		ret;
	char	*word;
	char	*expanded_word;

	j = 0;
	while (str[i + j] && !(check_oper(str[i + j])))
	{
		ret = quotes_handle(i + j, str, 34); // double quote
		if (ret == -1)
			return (-1);
		j += ret;
		ret = quotes_handle(i + j, str, 39); // single quote
		if (ret == -1)
			return (-1);
		j += ret;
		if (is_whitespace(str[i + j]))
			break ;
		j++;
	}
	word = ft_substr(str, i, j);
	word = remove_quotes(word);
	expanded_word = expand_env_var(word, envp_cpy);
	free(word);
	if (!expanded_word)
		return (-1);
	if (!add_node(expanded_word, WORD, lexer_list))
		return (-1);
	return (j);
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
		else if (check_env_var(&str[i]))
			j = handle_var_env(str, i, lexer_list, envp_cpy);
		else
			j = read_words(i, str, lexer_list, envp_cpy);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
