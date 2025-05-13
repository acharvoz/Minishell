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

//#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int len_envp(char **envp_cpy)
{
    int i;

    i = 0;
    while (envp_cpy[i] != NULL)
        i++;
    return (i);
}

int print_var_export(char **envp_cpy, int len_envp)
{
    int i;
    int l;

	i = 0;
    while (i < len_envp)
    {
		l = 0;
		write(1, "declare -x ", 11);
        while (envp_cpy[i][l])
        {
            ft_putchar_fd(envp_cpy[i][l], 1);
            l++;
        }
		write(1, "\n", 1);
        i++;
    }
	return (0);
}

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

int	validate_export_arg(char *str, char **envp_cpy)
{
	int	i;
	int l;
	char *tmp;

	i = 0;
	if (!str)
		return (0);
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '+' && str[i + 1] == '=')
	{
		i += 2;
		while (str[i])
		{
			tmp[n] = str[i];
			n++;
			i++;
		}
		while (ft_strncmp(tmp, envp_cpy[l], n) != 0)
		{
			l++;
			if (envp_cpy[l] == NULL)
				break ;
		}
		ft_strjoin(envp_cpy[l], tmp);
		update_export_var(envp_cpy[l], envp_cpy);	
		free(tmp);
	}
	return (1);
}

void	update_export_var(char *str, char **envp_cpy)
{
	int	i;
	int	l;

	i = len_envp_key(str);
	l = 0;
	while (envp_cpy[l])
	{
		if (ft_strncmp(str, envp_cpy[l]], i) == 0 && len_envp_key(envp_cpy[l]) == i)
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

int ft_export(char **args, char **envp_cpy)
{
	int		rst;

    if (!args || args[0] == NULL)
		return (print_var_export(envp_cpy, len_envp(envp_cpy)));
	while (*args)
	{
		rst = 0;
		if (export_var_exist(*args, envp_cpy) || validate_export_arg(*args))
		{
			update_export_var(*args, envp_cpy);
			rst = 1;
		}
		args++;
	}
	return (rst);
}
