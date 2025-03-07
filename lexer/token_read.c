/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:03:30 by acharvoz          #+#    #+#             */
/*   Updated: 2025/03/04 15:00:12 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_reader(char *str, t_lexer **lexer_list)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		i += skip_spaces(str, i);
		if (check_oper(str[i]))
			j = handle_operator(str, i, lexer_list);
		else if (check_env_var(&str[i]))
			j = handle_var_env(str, i, lexer_list);
		else
			j = read_words(i, str, lexer_list);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
