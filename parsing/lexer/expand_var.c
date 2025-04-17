/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:42:23 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/17 14:43:25 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_env_var2(char *str, int *i, char **envp_cpy, char *rst)
{
	int		j;
	char	*var_name;
	char	*env_value;

	j = *i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, *i + 1, j - *i - 1);
	env_value = change_var_env(envp_cpy, var_name);
	free(var_name);
	if (env_value)
		rst = ft_strjoin(rst, env_value);
	else
		rst = ft_strjoin(rst, "");
	if (env_value)
		free(env_value);
	*i = j;
	return (rst);
}

//expand les variables

char	*expand_env_var(char *str, char **envp_cpy, int i)
{
	char	*result;
	bool	in_single;
	bool	in_double;

	result = ft_strdup("");
	in_single = false;
	in_double = false;
	while (str[i])
	{
		if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
			&& !in_single)
			result = expand_env_var2(str, &i, envp_cpy, result);
		else
		{
			result = ft_strjoin_char(result, str[i]);
			i++;
		}
	}
	return (result);
}

//gere l'expander dans les quotes

char	*process_word(char *str, char **envp_cpy)
{
	char	*expanded_word;

	if (should_expand_var(str))
	{
		expanded_word = expand_env_var(str, envp_cpy, 0);
		free(str);
		str = expanded_word;
	}
	str = remove_quotes(str);
	return (str);
}
