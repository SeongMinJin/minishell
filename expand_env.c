/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:21 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:53:10 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_head(t_symbol *head);
static char		*expand_env_in_double_quote(char *str);
static t_symbol	*expand_env_out_quote(char *str);

t_symbol	*expand_env(t_symbol *symbol)
{
	t_symbol	*head;
	t_symbol	*new;

	head = new_symbol("");
	head->next = symbol;
	symbol->pre = head;
	while (symbol)
	{
		if (ft_strchr(symbol->str, '$'))
		{
			symbol->str = expand_env_in_double_quote(symbol->str);
			replace_white_space(symbol->str);
			new = expand_env_out_quote(symbol->str);
			symbol->str = NULL;
			backup_space_symbol(new);
			symbol = update_symbol(symbol, new);
		}
		else
			symbol = symbol->next;
	}
	symbol = head->next;
	if (symbol)
		symbol->pre = NULL;
	free_head(head);
	return (symbol);
}

static void	free_head(t_symbol *head)
{
	free(head->str);
	free(head);
}

static char	*expand_env_in_double_quote(char *str)
{
	int		idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == Q_SINGLE)
			skip_quote(&str[idx], &idx, Q_SINGLE);
		else if (str[idx] == Q_DOUBLE)
		{
			idx++;
			while (str[idx] != Q_DOUBLE)
			{
				if (str[idx] == '$')
					str = new_str(str, &str[idx + 1], &idx);
				else
					idx++;
			}
			idx++;
		}
		else
			idx++;
	}
	return (str);
}

static t_symbol	*expand_env_out_quote(char *str)
{
	int			idx;
	char		**str_2d;
	t_symbol	*head;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == Q_SINGLE || str[idx] == Q_DOUBLE)
			skip_quote(&str[idx], &idx, str[idx]);
		else if (str[idx] == '$')
			str = new_str(str, &str[idx + 1], &idx);
		else
			idx++;
	}
	head = NULL;
	str_2d = ft_split(str, "\n\t\v\f\r ");
	idx = 0;
	while (str_2d[idx])
	{
		add_back_symbol(&head, new_symbol(str_2d[idx]));
		free(str_2d[idx++]);
	}
	free(str_2d);
	free(str);
	return (head);
}
