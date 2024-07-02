/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:43:05 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/30 23:43:06 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	while ((a[i] == b[i]) && a[i] && b[i])
		i++;
	return (a[i] - b[i]);
}