/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:27 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:53:10 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_cnt(void)
{
	int			i;
	t_envlst	*env;

	i = 0;
	env = g_info->envlst;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**make_env(void)
{
	char		**str;
	t_envlst	*env;
	int			i;

	str = (char **)ft_calloc(sizeof(char *), env_cnt() + 1);
	if (!str)
		allocat_error();
	env = g_info->envlst;
	i = 0;
	while (env)
	{
		str[i] = ft_strjoin_free(ft_strjoin(env->key, "="), env->value);
		env = env->next;
		i++;
	}
	return (str);
}
