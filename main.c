/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:52:19 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/17 14:30:21 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Print l'error

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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**envp_cpy;

	(void)argc;
	(void)argv;
	envp_cpy = ft_strcpy_envp(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] != '\0')
			add_history(input);
		parsing_start(input, envp_cpy);
	}
	return (0);
}
