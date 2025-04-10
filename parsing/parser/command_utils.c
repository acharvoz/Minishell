/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:08:56 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/10 20:06:23 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_simple_cmds	*init_simple_cmd(void)
{
	t_simple_cmds	*cmd;

	cmd = malloc(sizeof(t_simple_cmds));
	if (!cmd)
		return (NULL);
	cmd->str = malloc(sizeof(char *));
	if (!cmd->str)
	{
		free(cmd);
		return (NULL);
	}
	cmd->str[0] = NULL;
	cmd->num_redirections = 0;
	cmd->hd_file_name = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	add_token_to_cmd(t_simple_cmds *cmd, t_lexer *tmp)
{
	int		count;
	char	**new_str;
	int		i;

	if (!cmd || !tmp)
		return ;
	count = 0;
	while (cmd->str[count])
		count++;
	new_str = malloc(sizeof(char *) * (count + 2));
	if (!new_str)
		return ;
	i = 0;
	while (i < count)
	{
		new_str[i] = cmd->str[i];
		i++;
	}
	new_str[count] = ft_strdup(tmp->str);
	new_str[count + 1] = NULL;
	free(cmd->str);
	cmd->str = new_str;
	print_cmd(cmd);
}
//fonction test pour afficher avant et apres les pipes.

void	print_cmd(t_simple_cmds *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->str)
		return ;
	while (cmd->str[i])
	{
		printf("%s ", cmd->str[i]);
		i++;
	}
	printf("\n");
}
