/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:44:54 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/03 21:40:14 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * print_error: prints the error message str.
 */

int	print_error(char *str)
{
	if (str)
		ft_printf(2, "Error: '%s'\n", str);
	else
		ft_printf(2, "Error\n");
	return (1);
}

/*
 * add_dir: adds a directory to the path.
 *
 * @pwd: current working directory.
 * @dir: directory to add.
 *
 * return: New path.
 *	NULL on failure.
 */

char	*add_dir(char *pwd, char *dir)
{
	char	*new_value;
	char	*full_path;

	full_path = ft_strjoin(pwd, "/");
	if (!full_path)
		return (NULL);
	new_value = ft_strjoin(full_path, dir);
	free(full_path);
	free(pwd);
	return (new_value);
}

/*
 * trim_string: Replace '/' with one '/' if there's multiple '/'.
 *
 * @str: The argument passed to cd.
 * @dirs: str splitted with '/'
 *
 * return: trimmed string.
 *	NULL on failure.
 */

char	*trim_string(char *str, char **dirs)
{
	char	*trimmed;
	char	*tmp;
	int		i;

	if (!ft_strcmp(str, "-") || count_char(str, '/') < 2)
		return (free_split(dirs), ft_strdup(str));
	trimmed = ft_strdup(dirs[0]);
	i = 0;
	while (dirs[++i])
	{
		if (ft_strlen(dirs[i]) > 0)
		{
			tmp = ft_strjoin(trimmed, "/");
			free(trimmed);
			trimmed = ft_strjoin(tmp, dirs[i]);
			free(tmp);
		}
	}
	if (str[0] == '/' && trimmed[0] != '/')
	{
		tmp = ft_strjoin("/", trimmed);
		free(trimmed);
		trimmed = tmp;
	}
	return (free_split(dirs), trimmed);
}

/*
 * change_dir: changes the PWD and OLDPWD in the environment variables.
 *
 * @pwd: Argument passed to cd.
 * @env: Address of the linked list containing the environment variables.
 *
 * return: 0 on success
 *	1 on failure.
 */

int	change_dir(char *pwd, t_envp **env)
{
	char	*dir;
	char	*new_dir;

	new_dir = trim_string(pwd, ft_split(pwd, "/"));
	if (!access(new_dir, F_OK))
	{
		if (chdir(new_dir) < 0)
			return (free(new_dir), print_error("chdir"));
		change_pwds(env, new_dir, 'd');
	}
	else if (ft_strcmp(new_dir, "-") == 0)
	{
		dir = ft_strdup(search_env(*env, "OLDPWD"));
		if (!dir)
			return (free(new_dir), ft_printf(2,
					"Error: cd: OLDPWD not set\n"), 1);
		if (chdir(dir) < 0)
			print_error("chdir");
		change_pwds(env, dir, 'd');
		printf("%s\n", dir);
		free(dir);
	}
	else
		return (free(new_dir), print_error("cd: no such file or directory"));
	return (free(new_dir), 0);
}

/*
 * cd_: changes the current working directory, and adjust
 * PWD and OLDPWD accordingly.
 *
 * @args: arguments passed to cd.
 * @env: Address of the linked list containing the environment variables.
 *
 * return: 0 on success
 *	1 on failure.
 */

int	cd_(char **args, t_envp **env)
{
	char	*dir;

	if (!args[0] || is_tilde(args[0], args[1]))
	{
		dir = search_env(*env, "HOME");
		if (!dir)
			return (print_error("HOME is not set"));
		if (chdir(dir) < 0)
			return (print_error("chdir"));
		dir = ft_strdup(dir);
		change_pwds(env, dir, 'h');
		free(dir);
		return (0);
	}
	if (args[1] && args[0])
		return (print_error("cd: too many arguments"));
	else
		return (change_dir(args[0], env));
	return (0);
}
