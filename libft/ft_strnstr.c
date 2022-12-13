/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:38:27 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_str(const char *str)
{
	int	cnt;

	cnt = 0;
	while (*str++)
		cnt++;
	return (cnt);
}

char	*ft_strnstr(const char *haystack,
					const char *needle,
					size_t len)
{
	int	i;
	int	j;
	int	len_hay;
	int	len_nee;

	len_hay = len_str(haystack);
	len_nee = len_str(needle);
	if (!(*needle))
		return ((char *)haystack);
	i = 0;
	while (i < len_hay - len_nee + 1 && (unsigned int)(i + len_nee) <= len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && j < len_str(needle))
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return ((char *) '\0');
}
