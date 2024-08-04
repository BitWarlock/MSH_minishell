/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:45:01 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/02 23:45:01 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * create_node: Creates 
 */

t_envp	*create_node(char *name, char *value)
{
	t_envp	*node;

	node = gc_malloc(sizeof(t_envp), 1);
	if (!node)
		return (ft_printf(2, "Error: Allocation\n"), NULL);
	node->name = ft_strdup(name);
	if (!strncmp(node->name, "OLDPWD", ft_strlen(node->name) + 1))
		node->value = NULL;
	else if (!value)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	addnode(t_envp **head, char *name, char *value)
{
	t_envp	*curr;
	t_envp	*node;

	node = create_node(name, value);
	if (!node)
		return ;
	if (!*head)
		*head = node;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
}
