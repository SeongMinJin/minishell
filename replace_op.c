/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:23:42 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:53:10 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*combine_str(char *s1, char *s2, char *s3, int *i);
static char	*get_op(char *str);
static int	get_num(char c);
static int	skip(char *line, int flag);

char	*replace_op(char *line)
{
	char	*op;
	char	*tmp;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == Q_DOUBLE || line[i] == Q_SINGLE)
			i += skip(&line[i], line[i]);
		op = get_op(&line[i]);
		if (op[1] != ' ')
		{
			tmp = line;
			line = combine_str(ft_substr(line, 0, i), op, \
			ft_strdup(&line[i + get_num(op[1])]), &i);
			free(tmp);
			i += 2;
		}
		else
		{
			i++;
			free(op);
		}
	}
	return (line);
}

static char	*combine_str(char *s1, char *s2, char *s3, int *i)
{
	char	*str;
	char	*tmp;

	if (s2[1] == OP_IN_HEREDOC || s2[1] == OP_OUT_HEREDOC || \
	s2[1] == OP_AND_IF || s2[1] == OP_OR_IF)
		*i += 2;
	else
		*i += 1;
	tmp = ft_strjoin(s1, s2);
	str = ft_strjoin(tmp, s3);
	free(tmp);
	free(s1);
	free(s2);
	free(s3);
	return (str);
}

static int	get_num(char c)
{
	if (c == OP_IN_HEREDOC || c == OP_OUT_HEREDOC || \
	c == OP_AND_IF || c == OP_OR_IF)
		return (2);
	else
		return (1);
}

static int	skip(char *line, int flag)
{
	char	*tmp;

	tmp = line;
	line++;
	if (flag == Q_DOUBLE)
	{
		while (*line && *line != Q_DOUBLE)
			line++;
		return (line - tmp);
	}
	else
	{
		while (*line && *line != Q_SINGLE)
			line++;
		return (line - tmp);
	}
}

static char	*get_op(char *str)
{
	char	op_str[4];

	op_str[0] = ' ';
	op_str[1] = ' ';
	op_str[2] = ' ';
	if (!ft_strncmp(str, "<<", 2))
		op_str[1] = OP_IN_HEREDOC;
	else if (!ft_strncmp(str, ">>", 2))
		op_str[1] = OP_OUT_HEREDOC;
	else if (!ft_strncmp(str, "||", 2))
		op_str[1] = OP_OR_IF;
	else if (!ft_strncmp(str, "&&", 2))
		op_str[1] = OP_AND_IF;
	else if (!ft_strncmp(str, "<", 1))
		op_str[1] = OP_IN_RID;
	else if (!ft_strncmp(str, ">", 1))
		op_str[1] = OP_OUT_RID;
	else if (!ft_strncmp(str, "|", 1))
		op_str[1] = OP_PIPE;
	else if (!ft_strncmp(str, "(", 1))
		op_str[1] = OP_LBRACE;
	else if (!ft_strncmp(str, ")", 1))
		op_str[1] = OP_RBRACE;
	op_str[3] = '\0';
	return (ft_strdup(op_str));
}
