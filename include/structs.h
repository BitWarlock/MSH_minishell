/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:59 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/09 00:06:14 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define MAX_HEREDOCS 16

typedef struct s_ast
{
	struct s_token	*token;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_envp
{
	struct s_envp	*next;
	char			*name;
	char			*value;
}		t_envp;

typedef struct s_gc
{
	void		*garbage;
	struct s_gc	*next;
}		t_gc;

typedef struct s_token
{
	char			*word;
	t_ast			*subtree;
	int				doc_num;
	int				type;
	int				name;
	int				left_pipe;
	int				right_pipe;
	char			**args;
	int				expand_wild;
	int				subshell;
	size_t			*expansion_indices;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*last;
}			t_token;

typedef struct s_shell
{
	char			*doc_files[MAX_HEREDOCS + 1];
	int				exit_status;
	int				stdin_copy;
	int				heredoc_trap;
	int				fork_err;
	size_t			*env_var_ends;
	size_t			ends_arr_index;
	int				is_heredoc;
	t_envp			*env;
	t_ast			*ast;
	struct termios	og_ter_attr;
}		t_shell;

#endif // !STRUCTS_H
