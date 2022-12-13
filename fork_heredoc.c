/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:43:09 by yujelee           #+#    #+#             */
/*   Updated: 2022/11/09 17:32:36 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_heredoc(char *limiter, int stdin_backup, char *heredoc_tmp)
{
	int	pid;
	int	exitcode;

	pid = fork();
	if (pid == 0)
	{
		set_child_signal();
		read_here_doc(limiter, stdin_backup, heredoc_tmp);
	}
	else
	{
		block_signal();
		waitpid(pid, &exitcode, 0);
		if (WIFSIGNALED(exitcode) && WTERMSIG(exitcode) == 2)
		{
			g_info->flag = 1;
			set_exit_code(1);
			set_signal();
			return (-1);
		}
	}
	set_signal();
	return (0);
}
