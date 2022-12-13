/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_symbol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:23:35 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:53:10 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_symbol	*new_symbol(char *str)
{
	t_symbol	*new;

	new = (t_symbol *)malloc(sizeof(t_symbol));
	if (!new)
		exit(1);
	new->str = ft_strdup(str);
	new->type = -1;
	new->pre = NULL;
	new->next = NULL;
	return (new);
}

void	add_back_symbol(t_symbol **head, t_symbol *new)
{
	t_symbol	*tmp;

	tmp = *head;
	if (!tmp)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->pre = tmp;
	}
}

t_symbol	*get_last_symbol(t_symbol *symbol)
{
	if (!symbol)
		return (NULL);
	while (symbol->next)
		symbol = symbol->next;
	return (symbol);
}

t_symbol	*make_symbol_lst(char **temp)
{
	t_symbol	*symbol_lst;
	t_symbol	*new;
	int			i;

	symbol_lst = NULL;
	i = 0;
	while (temp[i])
	{
		new = new_symbol(temp[i]);
		add_back_symbol(&symbol_lst, new);
		free(temp[i]);
		i++;
	}
	free(temp);
	return (symbol_lst);
}
