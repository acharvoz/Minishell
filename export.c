/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teandria <teandria@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:33:51 by teandria          #+#    #+#             */
/*   Updated: 2025/05/08 16:46:12 by teandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_export_value(t_env *env, char *str)
{
	int	length;

	if (env == NULL)
		return ;
	if (env->value)
		free(env->value);
	if (*str == '=')
		str++;
	length = ft_strlen(str);
	env->value = malloc(length + 1);
	length = 0;
	while (*str)
		env->value[length++] = *str++;
	env->value[length] = '\0';
}

int	find_env_variable(char *str, t_env *env)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i == 0)
		return (0);
	while (env)
	{
		if (!ft_strncmp(str, env->key, i) && ft_strlen(env->key) == i)
		{
			update_export_value(env, str + i);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

char	*get_env_value_by_key(char *key, t_env *env)
{
	size_t	i;

	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	if (i > 0 && key[i - 1] == '+')
		i--;
	while (env)
	{
		if (!ft_strncmp(key, env->key, i) && ft_strlen(env->key) == i)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*get_env_pointer_by_key(char *key, t_env *env)
{
	size_t	i;

	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	if (i > 0 && key[i - 1] == '+')
		i--;
	while (env)
	{
		if (!ft_strncmp(key, env->key, i) && ft_strlen(env->key) == i)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_export(char **args, t_env **env)
{
	int		result;
	t_env	*last_env;

	result = 0;
	if (!args || args[0] == NULL)
		return (print_exported_variables(*env));
	last_env = *env;
	while (last_env->next)
		last_env = last_env->next;
	while (*args)
	{
		if ((find_env_variable(*args, *env) && *args)
			|| validate_export_argument(*args, &result, *env))
		{
			args++;
			continue ;
		}
		add_export_entry(*args, &last_env);
		if (last_env->next)
			last_env = last_env->next;
		if (!last_env)
			result = 1;
		args++;
	}
	return (result);
}
