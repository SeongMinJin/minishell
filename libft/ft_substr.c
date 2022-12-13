/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:38:38 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*rv;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (ft_strlen((char *)s) < start)
		return (ft_strdup(""));
	if (len > (size_t)ft_strlen((char *)s))
		len = ft_strlen((char *)s);
	rv = (char *)malloc(len * sizeof(char) + 1);
	if (!rv)
		exit(1);
	i = 0;
	while (s[start + i] && i < len)
	{
		rv[i] = s[start + i];
		i++;
	}
	rv[i] = '\0';
	return (rv);
}
