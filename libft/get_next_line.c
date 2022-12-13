/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:38:47 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_buf(char **buf)
{
	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	return (NULL);
}

char	*set_next_buf(char *buf, char *line)
{
	char	*temp;
	int		i;

	if (!line)
		return (free_buf(&buf));
	if (ft_strchr_g(buf, '\n'))
	{
		i = 0;
		while (i <= (long long)ft_strlen_g(buf, '\n'))
			i++;
		temp = ft_strjoin_g(&(buf[i]), "", 0);
		if (!temp)
			return (NULL);
		if (buf)
			free_buf(&buf);
		buf = temp;
	}
	else
		return (free_buf(&buf));
	return (buf);
}

int	get_line(char *buf, char **line)
{
	long long	i;

	*line = NULL;
	if (!buf[0])
		return (1);
	if (!(ft_strchr_g(buf, '\n')))
	{
		*line = ft_strjoin_g(buf, "", 0);
		if (!(*line))
			return (0);
		return (1);
	}
	*line = (char *)ft_calloc_g(ft_strlen_g(buf, '\n') + 2, sizeof(char));
	if (!(*line))
		return (0);
	i = -1;
	while (++i <= (long long)ft_strlen_g(buf, '\n'))
		line[0][i] = buf[i];
	return (1);
}

int	read_buf(char **buf, int fd)
{
	char	*str;
	int		bytes;

	str = (char *)ft_calloc_g(BUFFER_SIZE + 1, sizeof(char));
	if (!str)
		return (0);
	while (!ft_strchr_g(*buf, '\n'))
	{
		bytes = read(fd, str, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		str[bytes] = '\0';
		*buf = ft_strjoin_g(*buf, str, 1);
		if (!buf)
		{
			free(str);
			return (0);
		}
	}
	if (str)
		free(str);
	return (1);
}

int	get_next_line(int fd, char **rv_line)
{
	static char	*buf;
	char		*line;

	if (!buf)
	{
		buf = ft_calloc_g(1, sizeof(char));
		if (!buf)
			return (-1);
	}
	if (!read_buf(&buf, fd))
	{
		free_buf(&buf);
		return (-1);
	}
	if (!get_line(buf, &line))
	{
		free_buf(&buf);
		return (-1);
	}
	buf = set_next_buf(buf, line);
	*rv_line = line;
	if (!(*rv_line))
		return (0);
	return (1);
}
