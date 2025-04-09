/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:03:30 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/09 18:53:26 by acharvoz         ###   ########.fr       */
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
	int quote;
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

//voir notes avant remove quotes
//"'$HOME'" -> 'expanded'
//trouver le cas ou 
char	*process_word(char *word, char **envp_cpy)
{
	int i;
	bool simple_quote;
	char	*expanded_word;

	i = 0;
	simple_quote = true;
	while(word[i] && word[i] != '\'')
		i++;
	if (word[i] == '\'')
	{
		i++;;
		while(word[i] && word[i] != '\'')
			i++;
		if (word[i] == '\'')
			simple_quote = false;
	}
	if (simple_quote == true)//implementer var_simple_double
	{
		expanded_word = expand_env_var(word, envp_cpy);
		free(word);
		word = expanded_word;
	}
	word = remove_quotes(word);
	return (word);
}

void	var_simple_double(char *str, char **envp_cpy)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(str[i] && str[i] != '\'')//parcours jusqu'a simple
		i++;
	if (str[i] == '\'')
	{
		while(str[j] != '\"' && str[j] != '\'')//reparcours jusqu'a double ou simple
			j++;
		if (str[j] == '\"' && j < i)//si j est double et qu'elle est avant la simple
		{
			//autoriser l'expanding et garder les simple quotes
		}
	}
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
