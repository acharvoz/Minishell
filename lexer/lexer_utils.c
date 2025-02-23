/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:13:27 by acharvoz          #+#    #+#             */
/*   Updated: 2025/02/23 20:04:39 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_words(int i, char *str, t_lexer **lexer_list)
{
	int	j;

	j = 0;
	while (str[i + j] && !(check_oper(str[i + j])))
	{
		j += quotes_handle(i + j, str, 34);
		j += quotes_handle(i + j, str, 39);
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
	t_lexer		*new_element;
	static int	i = 0;

	new_element = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->token = token;
	new_element->i = i++;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
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
	t_lexer	*node;

	node = ft_lexer_new(str, token);
	if (!node)
		return (0);
	ft_lexer_add_back(lexer_list, node);
	return (1);
}
