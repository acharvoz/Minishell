/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teandria <teandria@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:26:03 by teandria          #+#    #+#             */
/*   Updated: 2025/05/08 16:52:39 by teandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_identifier(char *key)
{
	int	i;

	i = 0;
	if (!key || ft_isdigit(key[0]))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset_var(char **envp_cpy, char *key)
{
	int		i;
	int 	j;
	int		key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (envp_cpy[i])
	{
		if (ft_strncmp(envp_cpy[i], key, key_len) == 0 && envp_cpy[i][key_len] == '=')
		{
			free(envp_cpy[i]);
			j = i;
			while (envp_cpy[j])
			{
				envp_cpy[j] = envp_cpy[j + 1];
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char *key, char **envp_cpy)
{
	int	i;

	i = 1;
	if (is_valid_identifier(key[i]))
		return(unset_var(envp_cpy, key[i]));
}
