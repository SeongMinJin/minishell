/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:38:35 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (c);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*rv;
	size_t			len_rv;
	unsigned int	start;
	unsigned int	end;

	if (!s1)
		return (NULL);
	start = 0;
	while (is_set(s1[start], set))
		start++;
	if (ft_strlen((char *)s1) == 0)
		end = 0;
	else
		end = ft_strlen((char *)s1) - 1;
	while (is_set(s1[end], set) && end > start)
		end--;
	if (end - start < 0)
		return (ft_strdup(""));
	len_rv = end - start + 1;
	rv = (char *)malloc(len_rv * sizeof(char) + 1);
	if (!rv)
		exit(1);
	ft_strlcpy(rv, s1 + start, len_rv + 1);
	return (rv);
}
