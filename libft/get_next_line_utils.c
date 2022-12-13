/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:38:44 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_g(char *s, char c)
{
	int	cnt;

	cnt = 0;
	if (!s)
		return (0);
	while (*s && *s != c)
	{
		s++;
		cnt++;
	}
	return (cnt);
}

void	*ft_calloc_g(size_t count, size_t size)
{
	unsigned char	*rv;
	unsigned int	i;

	if (count != 0 && size != 0)
		if (count / size > UINT_MAX / size || size / count > UINT_MAX / size)
			return (NULL);
	rv = (unsigned char *)malloc(count * size);
	if (!rv)
		exit(1);
	i = 0;
	while (i < count * size)
		rv[i++] = 0;
	return (rv);
}

char	*ft_strjoin_g(char *s1, char *s2, int need_free)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*rv;

	if (!s2)
		return ((char *)s1);
	len_s1 = ft_strlen_g(s1, '\0');
	len_s2 = ft_strlen_g(s2, '\0');
	rv = (char *)ft_calloc_g(len_s1 + len_s2 + 1, sizeof(char));
	if (!rv)
		return (NULL);
	ft_strlcpy_g(rv, s1, len_s1 + 1);
	ft_strlcpy_g(rv + len_s1, (char *)s2, len_s2 + 1);
	if (s1 && need_free)
	{
		free(s1);
		s1 = NULL;
	}
	return (rv);
}

char	*ft_strchr_g(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	return (0);
}

size_t	ft_strlcpy_g(char *dst,
						const char *src,
						size_t dstsize)
{
	unsigned int	len_src;
	unsigned int	i;

	i = 0;
	while (src[i])
		i++;
	len_src = i;
	i = 0;
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (len_src);
}
