/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:23:44 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:53:10 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_space(char *str)
{
	if (*str == ' ')
		*str *= -1;
	else if (*str == '\r')
		*str *= -1;
	else if (*str == '\t')
		*str *= -1;
	else if (*str == '\f')
		*str *= -1;
	else if (*str == '\n')
		*str *= -1;
	else if (*str == '\v')
		*str *= -1;
}

char	*double_quote(char *str)
{
	while (*str)
	{
		is_space(str);
		if (*str == '\"')
			return (str);
		++str;
	}
	return (NULL);
}

char	*single_quote(char *str)
{
	while (*str)
	{
		is_space(str);
		if (*str == '\'')
			return (str);
		++str;
	}
	return (NULL);
}

void	replace_white_space(char *str)
{
	while (*str)
	{
		if (*str == '\"')
			str = double_quote(++str);
		if (*str == '\'')
			str = single_quote(++str);
		str++;
	}
}
