/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:36:48 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	movemem(unsigned char *temp,
					const unsigned char *srctemp,
					size_t len)
{
	int	i;

	if (temp <= srctemp)
	{
		i = 0;
		while ((unsigned int)i < len)
		{
			temp[i] = srctemp[i];
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (i >= 0)
		{
			temp[i] = srctemp[i];
			i--;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*temp;
	const unsigned char	*srctemp;

	if (!dst && !src && len > 0)
		return (dst);
	temp = (unsigned char *)dst;
	srctemp = (unsigned char *)src;
	movemem(temp, srctemp, len);
	return (dst);
}
