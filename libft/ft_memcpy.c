/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:45:55 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 12:10:21 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	char	*desti;
	char	*source;

	if (!dest && !src)
		return (NULL);
	desti = (char *)dest;
	source = (char *)src;
	while (size-- > 0)
	{
		*desti++ = *source++;
	}
	return (dest);
}
/*
int	main(void)
{
	char    dest[20] = "poueeet";
	char    src[20] = "oou";
	//ft_memcpy(((void*)0), ((void*)0), 3);
	puts (memcpy(((void*)0), ((void*)0), 3));
}*/