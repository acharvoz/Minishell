/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teandria <teandria@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:10:22 by teandria          #+#    #+#             */
/*   Updated: 2025/05/07 20:10:22 by teandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_exported_variables(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp("_", env->key, ft_strlen(env->key)))
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	return (0);
}

void	add_export_entry(char *str, t_env **env)
{
	int		length;
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	(*env)->next = NULL;
	if (!new_env)
		return ;
	length = ft_strlen(str);
	if (ft_strchr(str, '='))
	{
		length = ft_strlen(ft_strchr(str, '=') + 1);
		new_env->value = ft_substr(str, ft_strlen(str) - length, length);
		length = ft_strlen(str) - length - 1;
	}
	else
		new_env->value = NULL;
	new_env->key = malloc(length + 1);
	new_env->key[length] = '\0';
	while (length-- > 0)
		new_env->key[length] = str[length];
	new_env->next = NULL;
	(*env)->next = new_env;
}

void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	while (*arg)
		write(2, arg++, 1);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	concat_export_value(char *arg, t_env *env, int i)
{
	char	*previous_value;
	char	*new_value;

	if (arg[i] == '+' && arg[i + 1] != '=')
		return (1);
	previous_value = get_env_value_by_key(arg, env);
	if (!previous_value)
		previous_value = "";
	new_value = ft_strjoin(previous_value, (arg + i + 2));
	update_export_value(get_env_pointer_by_key(arg, env), new_value);
	free(new_value);
	return (2);
}

int	validate_export_argument(char *arg, int *result, t_env *env)
{
	int	status;
	int	i;

	i = 0;
	if (!arg)
		return (0);
	status = 0;
	if (ft_isdigit(arg[0]) || arg[0] == '=')
		status = 1;
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			status = 1;
			break ;
		}
		i++;
	}
	if (arg[i] == '+')
		status = concat_export_value(arg, env, i);
	if (status == 1 && *result == 0)
		print_export_error(arg);
	if (status == 1)
		*result = status;
	return (status);
}
