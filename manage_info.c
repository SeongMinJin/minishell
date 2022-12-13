/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:23:29 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/09 15:56:33 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(char **env)
{
	g_info = (t_info *)malloc(sizeof(t_info));
	g_info->envlst = NULL;
	parse_env(env);
	g_info->exit_code = ft_itoa(0);
	g_info->oldpwd_flag = 0;
	g_info->home = get_env("HOME");
}

void	set_exit_code(int code)
{
	free(g_info->exit_code);
	g_info->exit_code = ft_itoa(code);
}
