/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:21:51 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_symbol	*find_last(t_symbol *symbol)
{
	t_symbol	*cmd_place;

	cmd_place = symbol;
	while (1)
	{
		if (!cmd_place->next)
			break ;
		if (cmd_place->next->type == T_PIPE)
			break ;
		cmd_place = cmd_place->next;
	}
	return (cmd_place);
}

void	swap_symbol(t_symbol *symbol)
{
	int		temp_type;
	char	*temp_str;

	temp_type = symbol->type;
	temp_str = symbol->str;
	symbol->type = symbol->next->type;
	symbol->str = symbol->next->str;
	symbol->next->type = temp_type;
	symbol->next->str = temp_str;
}

void	sort_redirection(t_symbol *symbol)
{
	t_symbol	*temp;

	symbol = find_last(symbol);
	while (symbol && symbol->type != T_PIPE)
	{
		if (symbol->type == T_CMD || symbol->type == T_ARG)
		{
			temp = symbol;
			while (temp->next && temp->next->type != T_PIPE && \
			temp->next->type != T_CMD && temp->next->type != T_ARG)
			{
				swap_symbol(temp);
				temp = temp->next;
			}
		}
		symbol = symbol->pre;
	}
}

t_token	*pipeline(t_symbol *symbol)
{
	t_token		*token;
	t_symbol	*tmp;

	if (!symbol)
		return (NULL);
	if (symbol->type == T_LBRACE)
		return (brace_group(symbol));
	else
	{
		token = make_token(symbol);
		tmp = token->symbol;
		while (tmp)
		{
			sort_redirection(tmp);
			tmp = tmp->next;
			while (tmp && tmp->type != T_PIPE)
				tmp = tmp->next;
		}
		return (token);
	}
}
