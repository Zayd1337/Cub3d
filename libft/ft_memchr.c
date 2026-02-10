/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:10:21 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 10:03:43 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	car;
	size_t			i;

	car = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == car)
		{
			str += i;
			return (str);
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
   char s[] = {0, 1, 2 ,3 ,4 ,5};

   //memchr(s, c, 5);
   printf("%s",   (unsigned char *)ft_memchr(s, 2, 3));
   //printf("%s",   (unsigned char *)ft_memchr(str, '!', 0));
   //printf("%p\n", s);
}*/