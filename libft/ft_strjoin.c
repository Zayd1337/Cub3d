/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:45:40 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 11:57:19 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	tnt_strlcat(char *cpy, char *s1, const char *s2)
{
	size_t	i;
	size_t	lens1;

	i = 0;
	lens1 = ft_strlen(s1);
	while (lens1--)
	{
		*cpy++ = *s1++;
		i++;
	}
	while (*s2)
	{
		*cpy++ = *s2++;
		i++;
	}
	*cpy = '\0';
	cpy = 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s1pc;
	char	*cpy;

	s1pc = (char *)s1;
	cpy = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!cpy)
	{
		return (NULL);
	}
	tnt_strlcat(cpy, s1pc, s2);
	return (cpy);
}

/*
int	main(void)
{
	printf("%s", ft_strjoin("pouet", "kaki"));
}*/