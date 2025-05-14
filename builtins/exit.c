/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teandria <teandria@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:31:33 by teandria          #+#    #+#             */
/*   Updated: 2025/05/08 16:48:26 by teandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric_argument(char *arg)
{
	int					i;
	unsigned long long	max_value;
	unsigned long long	number;

	max_value = 9223372036854775807ULL;
	i = 0;
	if (*arg == '-' || *arg == '+')
		arg++;
	if (ft_strlen(arg) > 19)
		return (1);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	number = 0;
	i = 0;
	while (arg[i])
	{
		number *= 10;
		number += arg[i] - '0';
		i++;
	}
	return (number > max_value);
}

int	ft_exit(char **args)
{
	if (!args || !args[0])
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (!is_numeric_argument(args[0]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	if (args[1])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	ft_putendl_fd("exit", 1);
	exit(ft_atoi(args[0]));
	return (0);
}
