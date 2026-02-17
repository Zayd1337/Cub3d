/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:45:40 by jeazil            #+#    #+#             */
/*   Updated: 2025/07/02 14:30:46 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		lens1;
	int		lens2;
	int		k;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!str)
		return (NULL);
	k = 0;
	while (*s1)
	{
		str[k] = *s1++;
		k++;
	}
	while (*s2)
	{
		str[k] = *s2++;
		k++;
	}
	str[k] = '\0';
	return (str);
}

/*
int	main(void)
{
	printf("%s", ft_strjoin("pouet", "kaki"));
}*/