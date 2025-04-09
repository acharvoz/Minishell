/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_read_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:42:23 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/09 18:14:36 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//fixe pour faire en sorte que ca expand dans tous les cas sauf les simple quotes

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

char	*expand_env_var2(char *str, int *i, char **envp_cpy, char *result)
{
	int		j;
	char	*var_name;
	char	*env_value;
	char	*temp;

	j = *i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, *i + 1, j - *i - 1);
	env_value = change_var_env(envp_cpy, var_name);
	free(var_name);
	temp = result;
	if (env_value)
		result = ft_strjoin(result, env_value);
	else
		result = ft_strjoin(result, "");
	free(temp);
	if (env_value)
		free(env_value);
	*i = j;
	return (result);
}

char	*expand_env_var(char *str, char **envp_cpy)
{
	int		i;
	char	*result;
	char	*temp;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			result = expand_env_var2(str, &i, envp_cpy, result);
		else
		{
			temp = result;
			result = ft_strjoin_char(result, str[i]);
			free(temp);
			i++;
		}
	}
	return (result);
}
