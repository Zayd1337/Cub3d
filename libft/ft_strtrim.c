/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:48:34 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 11:59:10 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkset(char s1, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy;
	size_t	i;
	size_t	start;
	size_t	len;

	start = 0;
	while (s1[start] && checkset(s1[start], set))
		start++;
	len = ft_strlen(s1);
	while (len > start && checkset(s1[len - 1], set))
		len--;
	cpy = (char *)malloc(sizeof(char) * (len - start + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (start < len)
		cpy[i++] = s1[start++];
	cpy[i] = 0;
	return (cpy);
}
/*int	main(void)
{
	char s1[] = "lorem ipsum dolor sit amet";
	printf("%s\n", ft_strtrim(s1, "te"));
}*/