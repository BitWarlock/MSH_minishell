/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:29:31 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/08 20:11:33 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Searches for the command in directories specified by
 * the PATH environment variable.
 * Returns the absolute path if the command is an absolute path.
 * If the command is not found in any of the directories, NULL is returned.
 */

char	*join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*new_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (perror("Malloc"), NULL);
	new_path = ft_strjoin(tmp, cmd);
	if (!new_path)
		return (perror("Malloc"), NULL);
	return (new_path);
}

char	*find_path(char *cmd, char *path_env)
{
	char	**paths;
	char	*path;
	int		i;

	if (cmd[0] == '/' && access(cmd, F_OK))
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ":");
	if (!paths)
		return (perror("Malloc"), NULL);
	i = 0;
	while (paths[i])
	{
		path = join_path(paths[i], cmd);
		if (!path)
			return (NULL);
		if (!access(path, F_OK))
			return (path);
		i++;
	}
	return (NULL);
}
