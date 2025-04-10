/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 03:38:42 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/10 17:43:46 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//gerer avec des espaces avant/apres

int	quotes_handle(int i, char *str, char del)
{
	int	j;

	if (str[i] != del)
		return (0);
	
	j = 1;
	while (str[i + j] && str[i + j] != del)
		j++;
	if (!str[i + j])
	{
		printf("Error: Quotes unclosed\n");
		return (-1);
	}
	return (j + 1);
}

//supprime les quotes dans la sortie finale

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		single_quote;
	int		double_quote;
	char	*new_str;

	new_str = malloc(strlen(str) + 1);
	i = 0;
	j = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
