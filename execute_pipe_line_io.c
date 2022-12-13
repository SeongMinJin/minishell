/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_line_io.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:24:35 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/09 17:25:53 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *file, int redirection_type)
{
	int	fd;

	fd = 0;
	if (redirection_type == T_IN_RID)
		fd = open(file, O_RDONLY);
	else if (redirection_type == T_OUT_RID)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else if (redirection_type == T_IN_HEREDOC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else if (redirection_type == T_OUT_HEREDOC)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 0)
		return (open_file_error(file));
	return (fd);
}

int	read_here_doc(char *limiter, int stdin_backup, char *heredoc_tmp)
{
	size_t	len_limiter;
	char	*line;
	int		status;
	int		fd;

	fd = open_file(heredoc_tmp, T_IN_HEREDOC);
	if (fd < 0)
		return (-1);
	len_limiter = ft_strlen(limiter);
	while (1)
	{
		write(2, ">", 1);
		status = get_next_line(stdin_backup, &line);
		if (status == -1)
			allocat_error();
		if (status == 0 || (line[ft_strlen(line) - 1] == '\n'\
				&& limiter && !ft_strncmp (line, limiter, \
					len_cmp(ft_strlen(line) - 1, len_limiter))))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}

int	dup_in_redirection(t_symbol *symbol, int type_rid, int stdin_backup, int i)
{
	int	fd_redirection;
	int	flag;

	fd_redirection = STDIN;
	flag = 0;
	if (type_rid == T_IN_RID)
	{
		fd_redirection = open_file(symbol->next->str, T_IN_RID);
		if (fd_redirection < 0)
			return (-1);
		if (count_after_rid(symbol))
			close(fd_redirection);
		flag = DID_IN_RID;
	}
	else if (type_rid == T_IN_HEREDOC)
		flag = task_here_doc(symbol, &fd_redirection, stdin_backup, i);
	if (flag == DID_IN_RID && !count_after_rid(symbol))
	{
		dup2(fd_redirection, STDIN);
		close(fd_redirection);
	}
	return (flag);
}

int	dup_out_redirection(t_symbol *symbol, int type_rid)
{
	int			fd_redirection;

	fd_redirection = STDOUT;
	fd_redirection = open_file(symbol->next->str, type_rid);
	if (fd_redirection < 0)
		return (-1);
	dup2(fd_redirection, STDOUT);
	close(fd_redirection);
	return (DID_OUT_RID);
}

int	dup_redirection(t_symbol *symbol, int stdin_backup, int i)
{
	int	in_flag;
	int	out_flag;
	int	type_rid;

	in_flag = 0;
	out_flag = 0;
	while (symbol && symbol->type != T_CMD)
	{
		type_rid = symbol->type;
		if (type_rid == T_PIPE)
			break ;
		if (type_rid == T_IN_RID || type_rid == T_IN_HEREDOC)
			in_flag = dup_in_redirection(symbol, type_rid, stdin_backup, i);
		else if (type_rid == T_OUT_RID || type_rid == T_OUT_HEREDOC)
			out_flag = dup_out_redirection(symbol, type_rid);
		if (in_flag < 0 || out_flag < 0)
			return (-1);
		symbol = symbol->next;
	}
	return (in_flag + out_flag);
}
