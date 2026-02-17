/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:22:04 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 11:57:47 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	lendest;
	size_t	lensrc;
	size_t	i;

	i = 0;
	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	if (size == 0)
		return (lensrc);
	if (size <= lendest)
		return (size + lensrc);
	while (i + lendest < size - 1 && src[i])
	{
		dest[lendest + i] = src[i];
		i++;
	}
	dest[lendest + i] = '\0';
	return (lendest + lensrc);
}

/*
int	main(void)
{
	char str1[20] = "kaki";
	char str2[20] = "pouet";

	//ft_strlcat(str1, str2,8) ;
	//printf("%s\n", str1);
	//VERIFIER LES RETOURS (dans une autre vie)
	//printf("%zu\n", strlcat(str1, str2, 3));
	printf("%zu\n", ft_strlcat(str1, str2, 3));
}*/