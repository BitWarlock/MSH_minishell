/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 05:44:16 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/09 00:27:34 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_in_heredoc(char *var, t_shell *sh, int expand_flag)
{
	char	*result;
	int		i;
	int		j;

	result = ft_strdup("");
	i = 0;
	j = 0;
	sh->is_heredoc = 1;
	while (var[i])
	{
		if (var[i] == '$')
		{
			if (expand_flag == 1)
				result = expand_(result, var, &i, sh);
			else
				result = copy_char(&i, var, result);
			j++;
		}
		else
			result = copy_char(&i, var, result);
	}
	return (result);
}

void	increment_vars(int *i, int *j, size_t *arr_index)
{
	(*i)++;
	(*j)++;
	(*arr_index)++;
}
