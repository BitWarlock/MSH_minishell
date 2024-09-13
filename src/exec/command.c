/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/08 20:13:19 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

/*
* Execute command (either a built-in or a normal command)
* Expand any arguments in the AST token.
* Copy the env if's not a built-in to pass it to the child process
*/

void	command(t_ast *ast, t_shell *sh)
{
	char	**env;

	if (!ast || ast->token->type != COMMAND
		|| sh->fork_err)
		return ;
	ast->token->args = check_expand(ast->token->args, sh, ast->token);
	if (!ast->token->args || !ast->token->args[0])
		return ;
	if (is_builtin(ast->token->args[0]))
		builtins_exe(ast->token->args[0], ast, sh);
	else
	{
		env = copy_env_to_arr(sh->env);
		if (!env)
			return (perror("env copy"));
		sh->exit_status = execute_cmd(ast->token->args, env, sh, ast);
	}
}

/*
 * Finds the path for the command and executes it.
 * If the command is part of a pipeline. It executes without fork.
 * Otherwise, it forks a new process to execute the command.
 */

void	child_proc(char *path, char **cmd, char *env[])
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(path, cmd, env);
	print_error(cmd[0], MSG_NOPERM);
	gc_malloc(0, 0);
	exit(ERR_NOPERM);
}

void	executes(char *path, char **cmd, char *env[])
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(path, cmd, env);
	print_error(cmd[0], MSG_NOPERM);
	gc_malloc(0, 0);
}

int	execute_with_fork(char *path, char **cmd, char *env[], t_shell *sh)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (fork_failed(sh->fork_err), 1);
	if (!pid)
		child_proc(path, cmd, env);
	else
	{
		if (waitpid(pid, &sh->exit_status, 0) < 0)
			return (perror("waitpid"), 1);
	}
	return (exit_status_code(sh->exit_status));
}

int	execute_cmd(char **cmd, char *env[], t_shell *sh, t_ast *ast)
{
	char	*path;
	char	*path_env;

	if (!access(ft_substr(cmd[0], 0, ft_strlen(cmd[0]) - 1), F_OK)
		&& cmd[0][ft_strlen(cmd[0]) - 1] == '/')
		return (print_error(cmd[0], "is a directory"), ERR_NOPERM);
	path_env = search_env(sh->env, "PATH");
	path = find_path(cmd[0], path_env);
	if (!path)
		return (print_error(cmd[0], MSG_NOCMD), ERR_NOCMD);
	if (!ft_strncmp(cmd[0], "ls", 3))
		cmd = ls_colored(cmd);
	if (!cmd)
		return (255);
	ignore_sigs();
	if (ast->token->left_pipe == 1 || ast->token->right_pipe == 1)
		executes(path, cmd, env);
	else
		return (execute_with_fork(path, cmd, env, sh));
	return (sh->exit_status);
}
