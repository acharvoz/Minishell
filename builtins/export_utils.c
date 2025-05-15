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

int	len_envp_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	return (i);
}

int	len_envp(char **envp_cpy)
{
	int	i;

	i = 0;
	while (envp_cpy[i] != NULL)
		i++;
	return (i);
}

int	print_var_export(char **envp_cpy, int len_envp)
{
	int	i;
	int	l;

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
