/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:52:19 by acharvoz          #+#    #+#             */
/*   Updated: 2025/03/10 13:43:49 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_lexer_token(t_lexer *lexer_list)
{
	t_lexer	*tmp = lexer_list;
	
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
	t_lexer	*lexer_list = NULL;
	char	**envp_cpy;

	(void)argc;
	(void)argv;
	envp_cpy = ft_strcpy_envp(envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break;
		if (input[0] != '\0')
			add_history(input);
		lexer_list = NULL;
		if (token_reader(input, &lexer_list, envp_cpy) == -1)
		{
			printf("Lexer Error\n");
			continue;
		}
		print_lexer_token(lexer_list);
	}
	return (0);
}

