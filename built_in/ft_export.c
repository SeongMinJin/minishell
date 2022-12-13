/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:24:21 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:52:47 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env(char *name, char *arg);
static void	print_export(void);
static char	*get_export_value(char *arg);
static char	*get_name(char *arg);

void	ft_export(char **arg, int pipe_cnt)
{
	char	*name;
	int		idx;

	if (pipe_cnt)
		ft_pipe_export(arg);
	if (!arg[1])
		return (print_export());
	idx = 1;
	while (arg[idx])
	{
		name = get_name(arg[idx]);
		if (!name)
		{
			print_error("export: `", arg[idx], "': not a valid identifier", 2);
			set_exit_code(127);
			return ;
		}
		set_env(name, arg[idx]);
		set_exit_code(0);
		free(name);
		++idx;
	}
}

static void	set_env(char *name, char *arg)
{
	char		*value;
	t_envlst	*tmp;

	value = get_export_value(arg);
	tmp = g_info->envlst;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->key))
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = value;
			}
			return ;
		}
		tmp = tmp->next;
	}
	ft_envlst_add_back(ft_envlst_new(name, value));
	if (value)
		free(value);
}

static char	*get_export_value(char *arg)
{
	int	idx;

	idx = 0;
	if (!ft_strchr(arg, '='))
		return (NULL);
	while (arg[idx] && arg[idx] != '=')
		idx++;
	return (ft_substr(arg, idx + 1, ft_strlen(arg) - idx - 1));
}

static char	*get_name(char *arg)
{
	int	idx;

	idx = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (NULL);
	while (arg[idx] && arg[idx] != '=')
	{
		if (!ft_isalnum(arg[idx]) && arg[idx] != '_')
			return (NULL);
		idx++;
	}
	return (ft_substr(arg, 0, idx));
}

static void	print_export(void)
{
	t_envlst	*temp;

	temp = g_info->envlst;
	while (temp)
	{
		write(1, "declare -x ", 11);
		write(1, temp->key, ft_strlen(temp->key));
		if (temp->value)
		{
			write(1, "=\"", 2);
			write(1, temp->value, ft_strlen(temp->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		temp = temp->next;
	}
}
