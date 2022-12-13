/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:40:21 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		get_next_line(int fd, char **rv_line);
int		read_buf(char **buf, int fd);
int		get_line(char *buf, char **line);
char	*set_next_buf(char *buf, char *line);
char	*free_buf(char **buf);
size_t	ft_strlen_g(char *s, char c);
void	*ft_calloc_g(size_t count, size_t size);
char	*ft_strjoin_g(char *s1, char *s2, int need_free);
char	*ft_strchr_g(char *s, int c);
size_t	ft_strlcpy_g(char *dst,
			const char *src,
			size_t dstsize);

#endif
