/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 05:44:23 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/01 05:44:23 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fork_failed(int fork_err)
{
	if (!fork_err)
		perror("fork");
	fork_err = 1;
	return ;
}

void	dup_stin(int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

int	set_exit_error(t_shell *sh, char *file, char *msg)
{
	sh->exit_status = print_error(file, msg);
	return (-1);
}

int	file_out_fd(char *token, t_ast *ast, t_shell *sh, char flag)
{
	char	*file;
	char	**expanded;
	char	**tmp;
	int		fd;

	expanded = check_expand((char *[]){token, NULL}, sh,
			ast->right->token);
	if (!expanded[0])
		return (set_exit_error(sh, token, "ambiguous redirect"));
	tmp = ft_split(expanded[0], " \t");
	if (expanded[0][0] == '\0' || expanded[1] || tmp[1])
		return (set_exit_error(sh, token, "ambiguous redirect"));
	file = expanded[0];
	if (flag == 'a')
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (set_exit_error(sh, file, MSG_NOPERM));
	return (fd);
}

int	file_in_fd(t_ast *ast, t_shell *sh, char *file)
{
	char	**expanded;
	char	**tmp;
	int		fd;

	expanded = check_expand((char *[]){file, NULL}, sh,
			ast->right->token);
	if (!expanded[0])
		return (set_exit_error(sh, file, "ambiguous redirect"));
	tmp = ft_split(expanded[0], " \t");
	if (expanded[0][0] == '\0' || tmp[1] || expanded[1])
		return (set_exit_error(sh, file, "ambiguous redirect"));
	file = expanded[0];
	if (ast->token->right_pipe)
	{
		if (access(file, F_OK))
			return (set_exit_error(sh, file, MSG_NOFILE));
		traverse_tree(ast->left, sh);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (set_exit_error(sh, file, MSG_NOPERM));
	return (fd);
}
