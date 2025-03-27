/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 03:38:42 by acharvoz          #+#    #+#             */
/*   Updated: 2025/03/27 16:26:13 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//gerer avec des espaces avant/apres

int	quotes_handle(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
		if (!str[i + j])
		{
			printf("Error: Quotes unclosed\n");
			return (-1);
		}
		j++;
	}
	return (j);
}
//supprime les quotes dans la sortie finale

char *remove_quotes(char *str)
{
	int len;

	len = ft_strlen(str);
	if ((str[0] == '"' || str[0] == '\'') && 
		(str[len - 1] == '"' || str[len - 1] == '\''))
	{
		char *new_str = malloc(len - 1);
		if (new_str == NULL)
			return (NULL);
		ft_strncpy(new_str, str + 1, len - 2);
		new_str[len - 2] = '\0';
		return (new_str);
	}
	return (str);
}
