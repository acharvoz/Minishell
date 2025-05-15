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

#include "../minishell.h"

int export_var_exist(char *str, char **envp_cpy)
{
	int	i;

	i = len_envp_key(str);
	while (*envp_cpy)
	{
		if (ft_strncmp(str, *envp_cpy, i) == 0 && len_envp_key(*envp_cpy) == i)
			return (1);
		envp_cpy++;
	}
	return (0);
}

void	update_export_var(char *str, char **envp_cpy)
{
	int	i;
	int	l;

	i = len_envp_key(str);
	l = 0;
	while (envp_cpy[l])
	{
		if (ft_strncmp(str, envp_cpy[l], i) == 0 && len_envp_key(envp_cpy[l]) == i)
		{
			free(envp_cpy[l]);
			envp_cpy[l] = ft_strdup(str);
			return ;
		}
		l++;
	}
	envp_cpy[l] = ft_strdup(str);
	envp_cpy[l + 1] = NULL;
}

int export_add_value(char *str, char **envp_cpy, int i)
{
	char *key = NULL;
	char *tmp = NULL;
	char *n_val = NULL;
	char *full = NULL;
	int l = 0;

	key = malloc(i + 1);
	if (!key)
		return (0);
	ft_strncpy(key, str, i);
	key[i] = '\0';

	tmp = ft_strdup(str + i + 2);
	if (!tmp)
	{
		free(key);
		return (0);
	}

	while (envp_cpy[l])
	{
		if (ft_strncmp(key, envp_cpy[l], i) == 0 && len_envp_key(envp_cpy[l]) == i)
		{
			char *old_val = ft_strchr(envp_cpy[l], '=');
			if (old_val)
			{
				n_val = ft_strjoin(key, "=");
				char *joined = ft_strjoin(n_val, old_val + 1);
				free(n_val);
				n_val = ft_strjoin(joined, tmp);
				free(joined);
			}
			else
			{
				n_val = ft_strjoin(key, "=");
				char *joined = ft_strjoin(n_val, tmp);
				free(n_val);
				n_val = joined;
			}
			free(envp_cpy[l]);
			envp_cpy[l] = n_val;
			free(key);
			free(tmp);
			return (1);
		}
		l++;
	}

	n_val = ft_strjoin(key, "=");
	full = ft_strjoin(n_val, tmp);
	free(n_val);
	envp_cpy[l] = full;
	envp_cpy[l + 1] = NULL;

	free(key);
	free(tmp);
	return (1);
}

int validate_export_arg(char *str, char **envp_cpy)
{
	int i = 0;

	if (!str || ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if ((str[i] == '+' && str[i + 1] == '='))
		return (export_add_value(str, envp_cpy, i));
	if (str[i] == '=' || str[i] == '\0')
		return (1);
	return (0);
}


int ft_export(char **args, char **envp_cpy)
{
	int	rst = 0;

	if (!args || args[0] == NULL)
		return (print_var_export(envp_cpy, len_envp(envp_cpy)));

	while (*args)
	{
		if (validate_export_arg(*args, envp_cpy) == 1 && !export_var_exist(*args, envp_cpy))
			update_export_var(*args, envp_cpy);
		args++;
	}
	return (rst);
}
