/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:36 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:53:10 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_len(char *env)
{
	int	len;

	len = 0;
	while (*env && *env != '=')
	{
		env++;
		len++;
	}
	return (len);
}

void	parse_env(char **env)
{
	char	**str;
	int		i;

	i = -1;
	while (env[++i])
	{
		str = ft_env_split(env[i]);
		ft_envlst_add_back(ft_envlst_new(str[0], str[1]));
		split_free(str);
	}
}

char	**ft_env_split(char *env)
{
	char	**splited_env;
	int		idx;

	splited_env = (char **)malloc(3 * sizeof(char *));
	if (!splited_env)
		exit(0);
	splited_env[0] = (char *)malloc((get_env_len(env) + 1) * sizeof(char));
	if (!splited_env[0])
		exit(0);
	idx = 0;
	while (*env && *env != '=')
		splited_env[0][idx++] = *env++;
	splited_env[0][idx] = 0;
	env++;
	splited_env[1] = (char *)malloc((get_env_len(env) + 1) * sizeof(char));
	if (!splited_env[1])
		exit(0);
	idx = 0;
	while (*env)
		splited_env[1][idx++] = *env++;
	splited_env[1][idx] = 0;
	splited_env[2] = NULL;
	return (splited_env);
}

char	*get_env(char *key)
{
	t_envlst	*tmp;
	int			len;

	if (*key == '?')
		return (ft_strdup(g_info->exit_code));
	tmp = g_info->envlst;
	len = ft_strlen(key);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value)
				return (ft_strdup(tmp->value));
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
