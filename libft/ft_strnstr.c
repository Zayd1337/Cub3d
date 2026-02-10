/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:21:41 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 10:04:12 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	found;

	i = 0;
	if (!little[i])
		return ((char *)big);
	while (i < len && big[i])
	{
		found = 0;
		if (big[i] == little[found])
		{
			while (i < len && big[i] && little[found]
				&& big[i] == little[found])
			{
				found++;
				i++;
			}
			if (little[found] == '\0')
				return ((char *)(big + i - found));
			else
				i = i - found;
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	size_t a = -1;
// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "aabc";
// 	printf("%s\n", ft_strnstr(haystack, needle, -1));
// 	printf("%zu\n", a);
// 	//printf("%s\n", strnstr(haystack, needle, -1));
// 	// printf("%s\n", ft_strnstr("popouetita", "pouet", 7));
// }
