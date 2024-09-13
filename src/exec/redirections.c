/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:38 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/07 12:00:28 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Redirects standard input or output based on the operation,
 *	and traverse_tree left to executes the command.
 *
 * (redirect_out) and (redirect_app): redirects standard output
 *	to a file (overwriting or appending to it's content).
 *
 * (redirect_in): redirects standard input from a file.
 */

void	redirect_out(t_ast *ast, t_shell *sh)
{
	int		fd;
	int		fd_out;

	if (!ast || ast->token->name != REDIR_OUT)
		return ;
	fd = file_out_fd(ast->right->token->word, ast, sh, 'o');
	if (fd == -1)
		return ;
	fd_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	traverse_tree(ast->left, sh);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	redirect_app(t_ast *ast, t_shell *sh)
{
	int		fd;
	int		fd_out;

	if (!ast || ast->token->name != REDIR_APP)
		return ;
	fd = file_out_fd(ast->right->token->word, ast, sh, 'a');
	if (fd == -1)
		return ;
	fd_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	traverse_tree(ast->left, sh);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	redirect_in(t_ast *ast, t_shell *sh)
{
	char	*file;
	int		fd;
	int		fd_in;

	if (!ast || ast->token->name != REDIR_IN)
		return ;
	file = ast->right->token->word;
	fd = file_in_fd(ast, sh, file);
	if (fd == -1)
		return ;
	fd_in = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	traverse_tree(ast->left, sh);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}
