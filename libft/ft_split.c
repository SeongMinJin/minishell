/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:37:25 by yujelee           #+#    #+#             */
/*   Updated: 2022/10/31 19:03:58 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_charset(char a, char *charset)
{
	while (*charset)
	{
		if (a == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	ft_count(char *str, char *charset)
{
	int		i;
	int		check;
	int		count;

	i = 0;
	check = 1;
	count = 0;
	while (str[i])
	{
		if (ft_charset(str[i], charset) == 1)
		{
			check = 1;
		}
		else
		{
			if (check == 1)
				count++;
			check = 0;
		}
		i++;
	}
	return (count);
}

char	*ft_strcpy(char *save, char *str, int s, int e)
{
	int		i;

	i = 0;
	while (s < e)
	{
		save[i] = str[s];
		i++;
		s++;
	}
	save[i] = 0;
	return (save);
}

char	**ft_putstr2(char **save, char *str, char *charset, int count)
{
	int		i;
	int		s;
	int		e;

	i = 0;
	s = 0;
	e = 0;
	while (i < count)
	{
		while (ft_charset(str[s], charset) == 1)
			s++;
		e = s;
		if (str[s] == 0)
			break ;
		while (ft_charset(str[e], charset) != 1 && str[e] != 0)
			e++;
		save[i] = (char *)malloc(e - s + 1);
		if (!save[i])
			exit(1);
		save[i] = ft_strcpy(save[i], str, s, e);
		i++;
		s = e;
	}
	return (save);
}

char	**ft_split(char *str, char *charset)
{
	int		count;
	char	**save;

	count = ft_count(str, charset);
	if (count == 0)
	{
		save = (char **)malloc(sizeof(char *));
		if (save == NULL)
			exit(1);
		save[0] = 0;
		return (save);
	}
	save = (char **)malloc(sizeof(char *) * (count + 1));
	if (save == NULL)
		exit(1);
	save[count] = NULL;
	save = ft_putstr2(save, str, charset, count);
	return (save);
}
