/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:27:40 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 11:58:02 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	char	*cdest;
	char	*csrc;
	size_t	i;

	i = 0;
	cdest = (char *)dest;
	csrc = (char *)src;
	if (size != 0 && ft_strlen(src) + 1 < size)
	{
		while (*csrc)
			*cdest++ = *csrc++;
		*cdest = '\0';
	}
	else if (size != 0)
	{
		while (i < size - 1)
		{
			cdest[i] = csrc[i];
			i++;
		}
		cdest[size - 1] = '\0';
	}
	return (ft_strlen(src));
}

// int	main(void)
// {
// 	char dest[15] = "";
// 	// char    src[6] = "cinq!";
// 	size_t cpy;
// 	ft_strlcpy(dest, "lorem ipsum dolor sit amet", 0);
// 	// strlcpy(dest, src, 6);
// 	printf("%s", dest);
// }