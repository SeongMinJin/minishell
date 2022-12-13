/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:13 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/09 17:30:08 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_built_in(char **cmd_arr, int pipe_cnt)
{
	if (!ft_strcmp("cd", cmd_arr[0]))
		ft_cd(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("echo", cmd_arr[0]))
		ft_echo(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("env", cmd_arr[0]))
		ft_env(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("exit", cmd_arr[0]))
		ft_exit(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("export", cmd_arr[0]))
		ft_export(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("pwd", cmd_arr[0]))
		ft_pwd(cmd_arr, pipe_cnt);
	else if (!ft_strcmp("unset", cmd_arr[0]))
		ft_unset(cmd_arr, pipe_cnt);
	else
		return (1);
	return (0);
}

void	execute_cmd(t_symbol *symbol, int pipe_cnt)
{
	char	*path;
	char	*cmd_path;
	char	**env;
	char	**cmd_arr;

	cmd_arr = make_cmd_arr(symbol);
	if (!cmd_arr)
		exit(0);
	path = get_env("PATH");
	cmd_path = get_cmd_path(cmd_arr[0], path);
	free(path);
	env = make_env();
	if (execute_built_in(cmd_arr, pipe_cnt))
		execve(cmd_path, cmd_arr, env);
	execute_error(cmd_path, cmd_arr, env);
}

static int	close_fd(int fd)
{
	close(fd);
	return (-1);
}

pid_t	fork_process(t_symbol *symbol, int pipe_cnt, int i, int stdin_backup)
{
	pid_t	pid;
	int		fd_pipe[2];
	int		flag;
	int		stdout_backup;

	stdout_backup = dup(STDOUT);
	flag = dup_redirection(symbol, stdin_backup, i);
	if (flag == -1)
		return (close_fd(stdout_backup));
	pipe(fd_pipe);
	pid = fork();
	if (pid > 0)
	{
		block_signal();
		dup_parant_pipe(fd_pipe, stdout_backup);
	}
	else
	{
		set_child_signal();
		dup_child_pipe(fd_pipe, flag, pipe_cnt, i);
		execute_cmd(symbol, pipe_cnt);
	}
	close(fd_pipe[0]);
	return (pid);
}

void	execute_pipe_line(t_symbol *symbol)
{
	pid_t	*pid_lst;
	int		pipe_cnt;
	int		i;
	int		stdin_backup;

	stdin_backup = dup(STDIN);
	pipe_cnt = get_pipe_cnt(symbol);
	if (execute_single_command(symbol, pipe_cnt, stdin_backup))
		return ;
	pid_lst = (pid_t *)malloc(sizeof(pid_t) * (pipe_cnt + 1));
	if (!pid_lst)
		exit(1);
	i = 0;
	while (symbol)
	{
		pid_lst[i] = fork_process(symbol, pipe_cnt, i, stdin_backup);
		if (pid_lst[i++] < 0)
			break ;
		while (symbol && symbol->type != T_PIPE)
			symbol = symbol->next;
		if (symbol)
			symbol = symbol->next;
	}
	wait_process(pid_lst, pipe_cnt + 1, stdin_backup);
	close(stdin_backup);
}
