/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:51:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/07 12:57:19 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Traverses the abstract syntax tree (AST) and applies various shell operations.
 * 
 * If the AST is valid and no fork error has occurred, the function sequentially
 * executes logical operations ('AND', 'OR'), pipe handling, redirections,
 * heredoc processing, and command execution.
 */

void	traverse_tree(t_ast *ast, t_shell *sh)
{
	if (!ast || sh->fork_err)
		return ;
	and_or_operators(ast, sh);
	pipe_operator(ast, sh);
	redirect_out(ast, sh);
	redirect_app(ast, sh);
	redirect_in(ast, sh);
	heredoc_apply(ast, sh);
	command(ast, sh);
}
