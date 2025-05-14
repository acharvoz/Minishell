/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teandria < teandria@student.42nice.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 02:13:25 by teandria          #+#    #+#             */
/*   Updated: 2025/04/12 01:52:36 by teandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args, int n)
{
	while (*args)
	{
		ft_putstr_fd(*args, 1);
		args++;
		if (*args)
			write (1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}
