/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:45:07 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/08 12:09:13 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

int	process_commands(t_shell *sh, char *str)
{
	if (check_line(str))
	{
		sh->ast = build_ast(str, sh);
		if (!sh->ast)
			sh->exit_status = 258;
		here_doc(sh->ast, sh);
		if (sh->heredoc_trap == 1)
		{
			sh->heredoc_trap = 0;
			return (free(str), 1);
		}
		traverse_tree(sh->ast, sh);
		close(sh->stdin_copy);
		sh->stdin_copy = -1;
		sh->fork_err = 0;
	}
	return (0);
}

void	command_loop(t_envp *envp, char *str, t_shell sh)
{
	char	*prev_line;

	prev_line = NULL;
	tcgetattr(STDIN_FILENO, &sh.og_ter_attr);
	while (1)
	{
		init_signal(&sh.exit_status);
		str = readline(ps1_prompt(search_env(envp, "PWD"),
					search_env(envp, "HOME"), sh.exit_status));
		init_signal(&sh.exit_status);
		if (!str)
			exit_(NULL, sh.exit_status);
		if ((!prev_line || ft_strncmp(prev_line, str, ft_strlen(prev_line) + 1))
			&& ft_strlen(str) > 1)
		{
			add_history(str);
			if (ft_strncmp(str, "", 1))
				prev_line = ft_strdup(str);
		}
		if (process_commands(&sh, str))
			continue ;
		tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &sh.og_ter_attr);
		free(str);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_shell	sh;
	char	*str;

	(void)argc;
	(void)argv;
	str = NULL;
	sh.stdin_copy = -1;
	sh.heredoc_trap = 0;
	sh.exit_status = 0;
	sh.fork_err = 0;
	init_envp(env, &sh.env);
	increment_shlvl(&sh.env);
	command_loop(sh.env, str, sh);
	free_envp(sh.env);
	return (0);
}
