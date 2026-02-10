/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:14:26 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 12:07:30 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char	*cdest;
	char	*csrc;

	if (!dest && !src)
		return (NULL);
	cdest = (char *)dest;
	csrc = (char *)src;
	if (dest <= src)
	{
		while (size--)
		{
			*cdest++ = *csrc++;
		}
	}
	else if (dest > src)
	{
		cdest += size - 1;
		csrc += size - 1;
		while (size--)
		{
			*cdest-- = *csrc--;
		}
	}
	return (dest);
}

/*
int	main(void)
{
	// char    dest[13] = "hohopouet";
	// char    src[13] = "poue";
	//ft_memmove(dest, src, 4);
	puts (memcpy(((void*)0), ((void*)0), 5));
}*/