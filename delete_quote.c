/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:04 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:53:10 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_quote(char *str)
{
	while (*str)
	{
		if (*str == Q_DOUBLE)
		{
			str++;
			while (*str != Q_DOUBLE)
			{
				if (*str == Q_SINGLE)
					*str *= -1;
				str++;
			}
		}
		if (*str == Q_SINGLE)
		{
			str++;
			while (*str != Q_SINGLE)
			{
				if (*str == Q_DOUBLE)
					*str *= -1;
				str++;
			}
		}
		str++;
	}
}

static int	quote_cnt(char *str)
{
	int	i;

	i = 0;
	while (*str++)
	{
		if (*str == Q_DOUBLE || *str == Q_SINGLE)
			i++;
	}
	return (i);
}

static void	replace_back_quote(char *str)
{
	while (*str)
	{
		if (*str < 0)
			*str *= -1;
		str++;
	}
}

void	delete_quote(t_symbol *symbol)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	replace_quote(symbol->str);
	tmp = (char *)ft_calloc(ft_strlen(symbol->str) - \
	quote_cnt(symbol->str) + 1, 1);
	while (symbol->str[i] != 0)
	{
		if (symbol->str[i] != Q_SINGLE && symbol->str[i] != Q_DOUBLE)
		{
			tmp[j] = symbol->str[i];
			j++;
		}
		i++;
	}
	free(symbol->str);
	replace_back_quote(tmp);
	symbol->str = tmp;
}
