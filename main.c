/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:52:19 by acharvoz          #+#    #+#             */
/*   Updated: 2025/03/27 15:53:48 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer_token(t_lexer *lexer_list)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	while (tmp)
	{
		printf("Token:[%s], Str:[%s]\n", get_token_name(tmp->token), tmp->str);
		tmp = tmp->next;
	}
}

//Lexer Error si une node n'a pas ete ajoutee

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**envp_cpy;

	(void)argc;
	(void)argv;
	envp_cpy = ft_strcpy_envp(envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (input[0] != '\0')
			add_history(input);
		parsing_start(input, envp_cpy);
	}
	return (0);
}
