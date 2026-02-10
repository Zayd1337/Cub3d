/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:10:38 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/07 15:12:14 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*toret;
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	str = (char *)s;
	len = ft_strlen(s);
	toret = malloc(sizeof(char) * (len + 1));
	if (!toret || !(f))
		return (NULL);
	while (i < len)
	{
		toret[i] = f(i, str[i]);
		i++;
	}
	toret[i] = '\0';
	return (toret);
}

/*
char	tnt_toupper(unsigned int nb, char c)
{
	(void)nb;
	if ((c >= 97 && c <= 122))
		return (c - 32);
	else
		return (c);
}
        
int	main(void)
{
	printf("%s\n", ft_strmapi("pouETttT", tnt_toupper));
}*/