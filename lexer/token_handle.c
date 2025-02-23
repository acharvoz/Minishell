/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 06:41:57 by acharvoz          #+#    #+#             */
/*   Updated: 2025/02/23 20:44:36 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Si operateur 'simple', check si 'double' puis ajoute a la liste chainee.

int	handle_operator(char *str, int i, t_lexer **lexer_list)
{
	t_tokens	token;

	token = check_oper(str[i]);
	if (token == GREAT && check_oper(str[i + 1]) == GREAT)
	{
		if (!add_node(NULL, GREAT_GREAT, lexer_list))
			return (-1);
		return (2);
	}
	else if (token == LESS && check_oper(str[i + 1]) == LESS)
	{
		if (!add_node(NULL, LESS_LESS, lexer_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_node(NULL, token, lexer_list))
			return (-1);
		return (1);
	}
	return (0);
}

//Check les operateurs 'simples'

t_tokens	check_oper(int c)
{
	int			i;
	static int	token_arr[3][2] = {
	{'|', PIPE},
	{'>', GREAT},
	{'<', LESS},
	};

	i = 0;
	while (i < 3)
	{
		if (token_arr[i][0] == c)
			return (token_arr[i][1]);
		i++;
	}
	return (0);
}

int	handle_var_env(char *str, int i, t_lexer **lexer_list)
{
	int	j;

	if (str[i] == '$' && (str[i + 1] == '_'
			|| (str[i + 1] >= 'A' && str[i + 1] <= 'Z')
			|| (str[i + 1] >= 'a' && str[i + 1] <= 'z')))
	{
		j = i + 1;
		while (str[j] && (str[j] == '_' || (str[j] >= 'A' && str[j] <= 'Z')
				|| (str[j] >= 'a' && str[j] <= 'z')
				|| (str[j] >= '0' && str[j] <= '9')))
			j++;
		if (!add_node(ft_substr(str, i, j - i), ENV_VAR, lexer_list))
			return (-1);
		return (j - i);
	}
	return (0);
}
