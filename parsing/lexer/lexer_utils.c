/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:18:44 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/17 14:36:38 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

//lance lexer/parser

void	parsing_start(char *input, char **envp_cpy)
{
	t_lexer	*lexer_list;
	int		i;

	i = 0;
	lexer_list = NULL;
	i = token_reader(input, &lexer_list, envp_cpy);
	if (i <= 0)
		return ;
	print_lexer_token(lexer_list);
	call_parser(&lexer_list);
	return ;
}

char	*ft_strjoin_char(char *s, char c)
{
	char	*new_str;
	int		len;
	int		i;

	if (!s)
		len = 0;
	else
		len = ft_strlen(s);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	return (new_str);
}

//copie l'env

char	**ft_strcpy_envp(char **envp)
{
	char	**envp_cpy;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	envp_cpy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_cpy)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		envp_cpy[i] = ft_strdup(envp[i]);
		if (!envp_cpy[i])
		{
			while (--i >= 0)
				free(envp_cpy[i]);
			free(envp_cpy);
			return (NULL);
		}
		i++;
	}
	envp_cpy[i] = NULL;
	return (envp_cpy);
}
