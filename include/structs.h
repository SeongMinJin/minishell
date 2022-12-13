/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:24:48 by yujelee           #+#    #+#             */
/*   Updated: 2022/11/09 15:56:24 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_info		t_info;
typedef struct s_envlst		t_envlst;
typedef struct s_symbol		t_symbol;
typedef struct s_token		t_token;
typedef struct s_cd			t_cd;

struct s_info
{
	t_envlst		*envlst;
	char			*home;
	char			*exit_code;
	int				oldpwd_flag;
	int				flag;
};

struct s_envlst
{
	char			*key;
	char			*value;
	t_envlst		*next;
};

struct	s_symbol
{
	int				type;
	char			*str;
	t_symbol		*pre;
	t_symbol		*next;
};

struct	s_token
{
	t_symbol	*symbol;
	t_token		*left;
	t_token		*right;
};

struct	s_cd
{
	char	*path;
	char	*cwd;
	char	*pwd;
	int		rv;
	int		pipe_cnt;
};

#endif
