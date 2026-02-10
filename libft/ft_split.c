/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:34:52 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 11:56:23 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static size_t	count_word(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*str == c && *str)
		str++;
	if (!*str)
		return (0);
	if (ft_strlen(str) == 1)
		return (1);
	while (str[i + 1])
	{
		if (((i == 0) || (str[i] == c && str[i + 1] != c)) && str[i + 1])
			count++;
		i++;
	}
	return (count);
}

static char	*fill(char *s, int len)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		nbword;
	int		lenword;
	int		which;

	nbword = count_word((char *)s, c);
	strs = (char **)malloc(sizeof(char *) * (nbword + 1));
	if (!strs)
		return (NULL);
	which = 0;
	while (which < nbword)
	{
		lenword = 0;
		while (*s == c)
			s++;
		while (s[lenword] != c && s[lenword])
			lenword++;
		strs[which] = fill((char *)s, lenword);
		if (!(strs[which]))
			return (ft_free(strs, which));
		s += lenword;
		which++;
	}
	strs[which] = NULL;
	return (strs);
}

// int	main(void)
// {
// 	printf("%s", fill(" pouet  u ", 1, 6));
// }

// int	main(void)
// {
// 	printf("%zu", count_word(" pouet  u ", ' '));
// }

// int	main(void)
// {
//    int i = 0;
//    char * * str = ft_split("--1-2--3---4----5-----42", '-');
//    while (i < 7)
//    {
// 		printf("%s\n", str[i]);
// 		i++;
//    }
// }