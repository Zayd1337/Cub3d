/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:37:11 by camsanch          #+#    #+#             */
/*   Updated: 2026/02/10 16:36:04 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
