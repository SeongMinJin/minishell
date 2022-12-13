/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:18 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:53:10 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *str, int *idx)
{
	int		len;
	char	*key;
	char	*value;

	len = 0;
	if (str[len] == '?')
	{
		*idx += 1;
		return (get_env("?"));
	}
	while (ft_isalnum(str[len]) || str[len] == '_')
	{
		len++;
		*idx += 1;
	}
	if (len == 0)
		return (NULL);
	key = ft_substr(str, 0, len);
	value = get_env(key);
	free(key);
	return (value);
}

void	skip_quote(char *str, int *idx, int flag)
{
	str++;
	if (flag == Q_SINGLE)
	{
		while (*str != Q_SINGLE)
		{
			str++;
			*idx += 1;
		}
		*idx += 2;
	}
	else
	{
		while (*str != Q_DOUBLE)
		{
			str++;
			*idx += 1;
		}
		*idx += 2;
	}
}

char	*new_str(char *str, char *key, int *idx)
{
	int		len;
	char	*value;
	char	*s1;
	char	*s2;
	char	*s3;

	len = 0;
	value = get_value(key, &len);
	if (!value)
	{
		*idx += 1;
		return (str);
	}
	s1 = ft_substr(str, 0, key - str - 1);
	s2 = ft_strjoin(s1, value);
	free(s1);
	s1 = ft_strdup(key + len);
	s3 = ft_strjoin(s2, s1);
	*idx += ft_strlen(value);
	free(s1);
	free(s2);
	free(str);
	free(value);
	return (s3);
}

void	backup_space_symbol(t_symbol *symbol)
{
	char	*str;
	int		idx;

	while (symbol)
	{
		str = symbol->str;
		idx = 0;
		while (str[idx])
		{
			if (str[idx] < 0 && str[idx] > -40)
				str[idx] *= -1;
			idx++;
		}
		symbol = symbol->next;
	}
}

t_symbol	*update_symbol(t_symbol *symbol, t_symbol *new)
{
	t_symbol	*tmp;

	if (new)
	{
		symbol->pre->next = new;
		new->pre = symbol->pre;
		if (symbol->next)
		{
			symbol->next->pre = get_last_symbol(new);
			get_last_symbol(new)->next = symbol->next;
		}
	}
	else
	{
		symbol->pre->next = symbol->next;
		if (symbol->next)
			symbol->next->pre = symbol->pre;
	}
	tmp = symbol->next;
	if (symbol->str)
		free(symbol->str);
	free(symbol);
	symbol = tmp;
	return (symbol);
}
