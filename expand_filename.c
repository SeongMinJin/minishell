/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:23 by yujelee           #+#    #+#             */
/*   Updated: 2022/11/02 15:10:26 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_need_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == Q_SINGLE)
		{
			i++;
			i += ft_strichr(&str[i], Q_SINGLE) + 1;
		}
		else if (str[i] == Q_DOUBLE)
		{
			i++;
			i += ft_strichr(&str[i], Q_DOUBLE) + 1;
		}
		else if (str[i] == '*')
			return (1);
		else
			i++;
	}
	return (0);
}

static int	word_compare(char **filename, char *wild, int *idx)
{
	while (**filename && wild[*idx] && wild[*idx] != '*')
	{
		if (wild[*idx] == **filename)
		{
			++(*idx);
			++(*filename);
		}
		else
			return (0);
	}
	if (wild[*idx] != '*' && **filename != wild[*idx])
		return (0);
	if (!wild[*idx] && **filename)
		return (0);
	return (1);
}

int	cmp_wild_card(char *filename, char *wild)
{
	int	idx;
	int	i;

	idx = 0;
	while (wild[idx])
	{
		if (wild[idx] == '*')
		{
			i = ft_strichr(filename, wild[idx + 1]);
			while (i >= 0)
			{
				if (cmp_wild_card(&filename[i], &wild[idx + 1]))
					return (1);
				++filename;
				i = ft_strichr(&filename[i], wild[idx + 1]);
			}
			++idx;
		}
		else
			if (!word_compare(&filename, wild, &idx))
				return (0);
	}
	return (1);
}

t_symbol	*get_file_lst(t_symbol *symbol)
{
	t_symbol		*file_lst;
	t_symbol		*file;
	DIR				*dirp;
	struct dirent	*file_entry;

	file_lst = NULL;
	dirp = opendir(".");
	file_entry = readdir(dirp);
	file_entry = readdir(dirp);
	file_entry = readdir(dirp);
	while (file_entry)
	{	
		if (cmp_wild_card(file_entry->d_name, symbol->str))
		{
			file = new_symbol(file_entry->d_name);
			file->type = symbol->type;
			add_back_symbol(&file_lst, file);
		}
		file_entry = readdir(dirp);
	}
	closedir(dirp);
	return (file_lst);
}

void	expand_filename(t_symbol *symbol)
{
	t_symbol	*file_lst;

	while (symbol)
	{
		if (symbol->type == 1 || symbol->type == 3 || symbol->type == 0)
		{
			if (is_need_expand(symbol->str) && symbol->type != T_CMD)
			{
				replace_wild_card(symbol->str);
				delete_quote(symbol);
				file_lst = get_file_lst(symbol);
				if (file_lst)
					symbol = update_symbol(symbol, file_lst);
				else
					symbol = symbol->next;
			}
			else
			{
				delete_quote(symbol);
				symbol = symbol->next;
			}
		}
		else
			symbol = symbol->next;
	}
}
