/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:03:30 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/07 15:12:03 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//unclosed quotes a fix
int var_quotes(int i, char *str, int *quote, int *j)
{
	if (str[i + *j] == 34 || str[i + *j] == 39)
	{
		*quote = quotes_handle(i + *j, str, str[i + *j]);
		if (*quote == -1)
			return (-1);
		*j += *quote;
	}
	return (0);
}
//gere la gestion du mot

int	read_words(int i, char *str, t_lexer **lexer_list, char **envp_cpy)
{
	int		j;
	int		quote;
	char	*word;

	j = 0;
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
	if (word[0] != '\'')  // Expansion only if not in single quotes
		word = expand_env_var(word, envp_cpy);
	// Remove quotes after expansion
	if (word[0] == '\'' && word[ft_strlen(word) - 1] == '\'')
		word = remove_simple_quotes(word);
	else if (word[0] == '"' && word[ft_strlen(word) - 1] == '"')
		word = remove_double_quotes(word);
	if (!add_node(word, WORD, lexer_list))
		return (-1);
	return (j);
}

//gere l'expander dans les quotes

char	*process_word(char *word, int j, char *str, char **envp_cpy)
{
	char	*expanded_word;

	if (str[0] == '\'' && str[j - 2] == '\'')
		word = remove_simple_quotes(word);
	else if (word[0] != '\'' && word[j - 1] != '\'')
	{
		expanded_word = expand_env_var(word, envp_cpy);
		free(word);
		word = expanded_word;
		if (word[0] == '"' && word[strlen(word) - 1] == '"')
			word = remove_double_quotes(word);
	}
	else
		word = remove_double_quotes(word);
	return (word);
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
