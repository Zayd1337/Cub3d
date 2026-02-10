/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:31 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 10:02:24 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int value, size_t count)
{
	size_t	i;

	i = 0;
	while (count-- > 0)
	{
		*(char *)dest++ = (char)value;
		i++;
	}
	dest = dest - i;
	return ((char *)dest);
}

/*
int	main(void)
{
	char    str[10] = "pouetaeiou";
	//memset(str, 49, 4);
	ft_memset(str, 49, 4);
	puts(str);
	//printf("%s\n", str);
}*/