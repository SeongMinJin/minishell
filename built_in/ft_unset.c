/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:24:27 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:52:47 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_vaild_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

static void	free_lst(t_envlst *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static void	delete_env_lst(char *str)
{
	t_envlst	*tmp;
	t_envlst	*free_tmp;

	tmp = g_info->envlst;
	if (!tmp)
		return ;
	if (ft_strcmp(tmp->key, str) == 0)
	{
		free_tmp = tmp;
		g_info->envlst = tmp->next;
		free(free_tmp);
		return ;
	}
	while (tmp->next)
	{
		if (ft_strcmp(tmp->next->key, str) == 0)
		{
			free_tmp = tmp->next;
			tmp->next = tmp->next->next;
			free_lst(free_tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_unset(char **arg, int pipe_cnt)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg_vaild_check(arg[i]))
		{
			print_error("unset: '", arg[i], "': not a valid identiier", 2);
			if (pipe_cnt)
				exit(1);
			set_exit_code(1);
			return ;
		}
		delete_env_lst(arg[i]);
		i++;
	}
	if (pipe_cnt)
		exit(0);
	set_exit_code(1);
	return ;
}
