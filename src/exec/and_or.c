/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:18 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:52:19 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Executes logical 'AND' and 'OR' operations.
 * 
 * The 'and_operator' function processes the left subtree 
 *		if successful, processes the right.
 *
 * The 'or_operator' function processes the left subtree 
 *		if unsuccessful, processes the right.
 *
 * The 'and_or_operators' function executes both operations sequentially.
 */

void	and_operator(t_ast *ast, t_shell *sh)
{
	if (!ast
		|| ast->token->name != AND)
		return ;
	traverse_tree(ast->left, sh);
	if (sh->exit_status == 0)
		traverse_tree(ast->right, sh);
}

void	or_operator(t_ast *ast, t_shell *sh)
{
	if (!ast
		|| ast->token->name != OR)
		return ;
	traverse_tree(ast->left, sh);
	if (sh->exit_status != 0)
		traverse_tree(ast->right, sh);
}

void	and_or_operators(t_ast *ast, t_shell *sh)
{
	and_operator(ast, sh);
	or_operator(ast, sh);
}
