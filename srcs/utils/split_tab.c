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
