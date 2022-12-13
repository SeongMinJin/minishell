/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:23:52 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/04 15:53:10 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_origin_op(int type)
{
	if (type == T_PIPE)
		return ("|");
	else if (type == T_AND_IF)
		return ("&&");
	else if (type == T_OR_IF)
		return ("||");
	else if (type == T_LBRACE)
		return ("(");
	else if (type == T_RBRACE)
		return (")");
	else if (T_IN_RID <= type && type <= T_OUT_HEREDOC)
		return ("newline");
	return (0);
}

int	syntax_error_token(char *str)
{
	if (str[0] < 0)
		str = get_origin_op(classify_op(str));
	print_error("syntax error near unexpected token '", str, "'", 2);
	set_exit_code(127);
	return (1);
}

int	check_expression_error(t_symbol *symbol)
{
	int	lbrace_in_row;
	int	rbrace_in_row;

	lbrace_in_row = 0;
	rbrace_in_row = 0;
	if (symbol->type == T_LBRACE)
		++lbrace_in_row;
	symbol = symbol->next;
	while (symbol)
	{
		if (symbol->pre->type != T_LBRACE && symbol->type == T_LBRACE)
			lbrace_in_row = 1;
		else if (symbol->type == T_LBRACE)
			++lbrace_in_row;
		else if (symbol->pre->type != T_RBRACE && symbol->type == T_RBRACE)
			rbrace_in_row = 1;
		else if (symbol->type == T_RBRACE)
			++rbrace_in_row;
		else
			rbrace_in_row = 0;
		if (lbrace_in_row > 1 && rbrace_in_row > 1)
			return (1);
		symbol = symbol->next;
	}
	return (0);
}

int	check_unexpected_token(t_symbol *symbol_lst)
{
	while (symbol_lst->next)
	{
		if (lbrace_case(symbol_lst))
			return (1);
		if (rbrace_case(symbol_lst))
			return (1);
		if (pipe_andif_orif_case(symbol_lst))
			return (1);
		if (direction_case(symbol_lst))
			return (1);
		symbol_lst = symbol_lst->next;
	}
	if (symbol_lst->pre && symbol_lst->pre->type == \
	T_RBRACE && symbol_lst->type != T_RBRACE)
		return (syntax_error_token(symbol_lst->str));
	if (symbol_lst->type >= T_PIPE && symbol_lst->type != T_RBRACE)
		return (syntax_error_token(get_origin_op(symbol_lst->type)));
	return (0);
}

int	validate(t_symbol *symbol_lst)
{
	if (check_first_type(symbol_lst->type))
		return (syntax_error_token(get_origin_op(symbol_lst->type)));
	if (check_unexpected_token(symbol_lst))
		return (1);
	if (check_expression_error(symbol_lst))
	{
		error_msg("syntax error in expression");
		return (1);
	}
	return (0);
}
