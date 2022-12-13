/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:38:24 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char			*rv;
	unsigned int	i;

	if (!s1)
		exit(1);
	i = 0;
	while (s1[i])
		i++;
	if (i < n)
		rv = (char *)malloc(i * sizeof(char) + 1);
	else
		rv = (char *)malloc(n * sizeof(char) + 1);
	if (!rv)
		exit(1);
	i = 0;
	while (i < n && s1[i])
	{
		rv[i] = s1[i];
		i++;
	}
	rv[i] = '\0';
	return (rv);
}
