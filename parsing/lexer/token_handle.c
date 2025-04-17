/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 06:41:57 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/17 14:37:24 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Si operateur 'simple', check si 'double' puis ajoute a la liste chainee.

int	handle_operator(char *str, int i, t_lexer **lexer_list)
{
	t_tokens	token;
	char		*op_str;

	token = check_oper(str[i]);
	if (token == GREAT && check_oper(str[i + 1]) == GREAT)
	{
		op_str = ft_strdup(">>");
		if (!op_str || !add_node(op_str, GREAT_GREAT, lexer_list))
			return (-1);
		return (2);
	}
	else if (token == LESS && check_oper(str[i + 1]) == LESS)
	{
		op_str = ft_strdup("<<");
		if (!op_str || !add_node(op_str, LESS_LESS, lexer_list))
			return (-1);
		return (2);
	}
	else
	{
		op_str = ft_substr(str, i, 1);
		if (!op_str || !add_node(op_str, token, lexer_list))
			return (-1);
		return (1);
	}
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

//trouver et return la valeur de la var d'env grace a la copie

char	*change_var_env(char **envp_cpy, char *var_env)
{
	int		i;
	char	*value;
	size_t	var_len;

	if (!envp_cpy || !var_env)
		return (NULL);
	var_len = ft_strlen(var_env);
	i = 0;
	while (envp_cpy[i])
	{
		if (ft_strncmp(envp_cpy[i], var_env, var_len) == 0
			&& envp_cpy[i][var_len] == '=')
		{
			value = ft_strdup(envp_cpy[i] + var_len + 1);
			if (!value)
			{
				printf("");
				return (NULL);
			}
			return (value);
		}
		i++;
	}
	return (NULL);
}
