/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:10 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/09 17:18:02 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_process(pid_t *pid, int pipe_cnt, int stdin_backup)
{
	int	exit_code;
	int	i;

	i = 0;
	while (i < pipe_cnt)
	{
		waitpid(pid[i], &exit_code, 0);
		i++;
	}
	free(pid);
	if (WIFSIGNALED(exit_code))
	{
		if (g_info->flag == 1)
			set_exit_code(1);
		else
			set_exit_code(WTERMSIG(exit_code) + 128);
	}
	else if (WIFEXITED(exit_code))
		set_exit_code(WEXITSTATUS(exit_code));
	dup2(stdin_backup, STDIN);
}

int	get_pipe_cnt(t_symbol *symbol)
{
	int	cnt;

	cnt = 0;
	while (symbol)
	{
		if (symbol->type == T_PIPE)
			cnt++;
		symbol = symbol->next;
	}
	return (cnt);
}

int	count_until_pipe(t_symbol *symbol)
{
	int	count;

	count = 0;
	while (symbol && symbol->type != T_PIPE)
	{
		symbol = symbol->next;
		++count;
	}
	return (count);
}

char	**make_cmd_arr(t_symbol *symbol)
{
	int		idx;
	int		count;
	char	**ret;

	while (symbol->next != NULL && symbol->next->type != T_PIPE
		&& symbol->type != T_CMD)
		symbol = symbol->next;
	if (symbol->type != T_CMD)
		return (NULL);
	count = count_until_pipe(symbol);
	ret = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!ret)
		allocat_error();
	idx = 0;
	while (idx < count)
	{
		ret[idx] = ft_strdup(symbol->str);
		symbol = symbol->next;
		++idx;
	}
	return (ret);
}

int	is_built_in(char **cmd_arr)
{
	if (!cmd_arr)
		return (0);
	if (!ft_strcmp("cd", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("echo", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("env", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("exit", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("export", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("pwd", cmd_arr[0]))
		return (1);
	else if (!ft_strcmp("unset", cmd_arr[0]))
		return (1);
	else
		return (0);
}
