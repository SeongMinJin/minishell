/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:36:30 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_num(int n)
{
	int	cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
		cnt++;
	while (n != 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	char		*rv;
	long long	num;
	int			i;
	int			neg;

	neg = 1;
	rv = (char *)malloc(len_num(n) * sizeof(char) + 1);
	if (!rv)
		exit(1);
	num = n;
	if (n < 0)
	{
		neg = 0;
		rv[0] = '-';
		num *= -1;
	}
	i = 0;
	while (i < (int)len_num(n) + neg - 1)
	{
		rv[len_num(n) - i - 1] = num % 10 + '0';
		num /= 10;
		i++;
	}
	rv [len_num(n)] = 0;
	return (rv);
}
