/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:52:46 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/17 14:31:04 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//parcourir dans la liste chainee.

void	call_parser(t_lexer **lexer_list)
{
	t_simple_cmds	*cmd_list;

	cmd_list = build_cmd_list(lexer_list);
}

//creer ma liste de commande

t_simple_cmds	*build_cmd_list(t_lexer **lexer_list)
{
	t_simple_cmds	*cmd_list;
	t_simple_cmds	*new_cmd;
	t_simple_cmds	*last_cmd;

	cmd_list = NULL;
	last_cmd = NULL;
	while (*lexer_list)
	{
		new_cmd = section_pipe(lexer_list);
		if (!new_cmd)
			break ;
		if (!cmd_list)
			cmd_list = new_cmd;
		else
			last_cmd->next = new_cmd;
		last_cmd = new_cmd;
	}
	return (cmd_list);
}

//separe ma ligne tokenisee en troncons autour des pipes

t_simple_cmds	*section_pipe(t_lexer **lexer_list)
{
	t_lexer			*tmp;
	t_simple_cmds	*cmd;

	if (!lexer_list || !*lexer_list)
		return (NULL);
	cmd = init_simple_cmd();
	tmp = *lexer_list;
	while (tmp && tmp->token != PIPE)
	{
		add_token_to_cmd(cmd, tmp);
		tmp = tmp->next;
	}
	if (tmp && tmp->token == PIPE)
		*lexer_list = tmp->next;
	else
		*lexer_list = NULL;
	return (cmd);
}
