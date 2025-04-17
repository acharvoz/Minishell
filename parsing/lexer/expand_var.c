/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:42:23 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/17 14:25:37 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_env_var2(char *str, int *i, char **envp_cpy, char *result)
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
		result = ft_strjoin(result, env_value);
	else
		result = ft_strjoin(result, "");
	if (env_value)
		free(env_value);
	*i = j;
	return (result);
}

//expand les variables -> si expand pas 1 alors expand aucune a fix

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
