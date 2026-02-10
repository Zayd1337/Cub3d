/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:16:27 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 11:57:08 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	if (!(f))
		return ;
	while (s[i])
	{
		(*f)(i, s + i);
		i++;
	}
}
/*
void	tnt_toupper(unsigned int nb, char *c)
{
	(void)nb;
	if ((c[nb] >= 97 && c[nb] <= 122))
		c[nb] -= 32;
}

int	main(void)
{
	char    str[] = "pOueTTtT";
	ft_striteri(str, tnt_toupper);
	printf("%s\n", str);
}*/