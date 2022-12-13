/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:39:24 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:53:10 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg1, char *msg2, char *msg3, int type)
{
	if (type < 0)
		type *= -1;
	else
	{
		ft_putstr_fd(SHELL, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putstr_fd(msg1, STDERR);
	if (type >= 1)
		ft_putstr_fd(msg2, STDERR);
	if (type >= 2)
		ft_putstr_fd(msg3, STDERR);
	ft_putstr_fd("\n", STDERR);
}

void	allocat_error(void)
{
	print_error("Allocate Error!", NULL, NULL, 0);
	exit(errno);
}

int	error_msg(char *str)
{
	print_error(str, NULL, NULL, 0);
	set_exit_code(127);
	return (0);
}

void	execute_error(char *cmd_path, char **cmd_arr, char **env)
{
	(void)env;
	(void)cmd_arr;
	(void)cmd_path;
	if (errno == 13)
		print_error(strerror(errno), NULL, NULL, 0);
	else
		print_error("command not found: ", cmd_arr[0], NULL, 1);
	if (cmd_path)
		free(cmd_path);
	if (cmd_arr && *cmd_arr)
		split_free(cmd_arr);
	if (env)
		split_free(env);
	exit(127);
}

int	open_file_error(char *file)
{
	print_error(file, ": ", strerror(errno), 2);
	return (-1);
}
