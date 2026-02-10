/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:16:28 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 11:59:58 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	if (start >= ft_strlen(s) || start == 4294967295)
		len = 0;
	if (start == 4294967295)
		start = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new = (char *)malloc(sizeof(char const) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*
int	main(void)
{
	printf("%s\n", ft_substr("", 0, 1));
}
*/