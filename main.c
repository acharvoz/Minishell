/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:52:19 by acharvoz          #+#    #+#             */
/*   Updated: 2025/02/23 20:38:10 by acharvoz         ###   ########.fr       */
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

int	main(void)
{
	char	*input;
	t_lexer	*lexer_list = NULL;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break;
		if (input[0] != '\0')
			add_history(input);
		lexer_list = NULL;
		if (token_reader(input, &lexer_list) == -1)
		{
			printf("Lexer Error\n");
			continue;
		}
		print_lexer_token(lexer_list);
	}
	return (0);
}
