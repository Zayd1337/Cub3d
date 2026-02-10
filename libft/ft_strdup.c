/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:15:31 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 11:56:55 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*str;
	char	*toret;

	size = ft_strlen(s) + 1;
	toret = malloc(sizeof(char) * size);
	if (!toret)
		return (NULL);
	str = toret;
	while (*s)
	{
		*str++ = *s++;
	}
	*str = 0;
	return (toret);
}
/*
int	main(void)
{
	printf("%s\n", ft_strdup("!@#$%^76787e nn"));
}
*/