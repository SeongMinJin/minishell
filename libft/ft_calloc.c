/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:36:02 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*rv;
	unsigned int	i;

	if (count != 0 && size != 0)
		if (count / size > UINT_MAX / size || size / count > UINT_MAX / size)
			exit(1);
	rv = (unsigned char *)malloc(count * size);
	if (!rv)
		exit(1);
	i = 0;
	while (i < count * size)
		rv[i++] = 0;
	return (rv);
}
