/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:43:15 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/18 09:43:16 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	count_words(char const *str, char *rm)
{
	size_t	nb_word;
	bool	on_word;

	nb_word = 0;
	on_word = false;
	while (*str)
	{
		if (ft_strchr(rm, *str) != 0 && on_word == false)
		{
			on_word = true;
			nb_word++;
		}
		else if (ft_strchr(rm, *str) == 0)
			on_word = false;
		str++;
	}
	return (nb_word);
}

char	**split_tab(char const *s, char *rm)
{
	char	**res;
	size_t	i;
	size_t	len;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, rm);
	res = ft_calloc(words + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && ft_strchr(rm, *s))
			s++;
		len = 0;
		while (s[len] && !ft_strchr(rm, s[len]))
			len++;
		res[i++] = ft_substr(s, 0, len);
		s += len;
	}
	return (res);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

char	*set_len(char *line, int len)
{
	char	*toret;
	int		i;

	if (len == 0)
		return (NULL);
	toret = malloc(sizeof(char) * (len + 1));
	if (!toret)
		return (NULL);
	i = 0;
	while (*line)
	{
		toret[i++] = *line;
		line++;
	}
	while (i < len)
		toret[i++] = ' ';
	toret[i] = '\0';
	return (toret);
}
