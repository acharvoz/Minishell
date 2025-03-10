/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:13:27 by acharvoz          #+#    #+#             */
/*   Updated: 2025/03/10 14:09:53 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_words(int i, char *str, t_lexer **lexer_list)
{
	int	j;

	j = 0;
	while (str[i + j] && !(check_oper(str[i + j])))
	{
		j += quotes_handle(i + j, str, 34);//double quote
		j += quotes_handle(i + j, str, 39);//single quote
		if (is_whitespace(str[i + j]))
			break ;
		j++;
	}
	if (!add_node(ft_substr(str, i, j), WORD, lexer_list))
		return (-1);
	
	return (j);
}

int	skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (is_whitespace(str[i + j]))
		j++;
	return (j);
}
//creer un element 'token' de ma liste doublement chainee

t_lexer	*ft_lexer_new(char *str, int token)
{
	t_lexer	*new_node;

	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	if (str)
		new_node->str = ft_strdup(str);
	else
		new_node->str = NULL;
	new_node->token = token;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
//ajoute a la fin de la liste chainee

void	ft_lexer_add_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
//creer la node et l'ajoute a la fin de la liste chainee

int	add_node(char *str, t_tokens token, t_lexer **lexer_list)
{
	t_lexer	*new_node;

	new_node = ft_lexer_new(str, token);
	if (!new_node)
		return (0);
	ft_lexer_add_back(lexer_list, new_node);
	return (1);
}
