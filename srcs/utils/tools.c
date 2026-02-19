#include "../../includes/cube3d.h"

int	count_ocurr(char *str, char c)
{
	int	count;
	int	i;

	if (!str)
		return (-1);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	count_elems(char **map, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (map[i] != NULL)
	{
		count += count_ocurr(map[i], c);
		i++;
	}
	return (count);
}

char *remove_chars(char *line, char *to_rm)
{
	int i;
	int k;
	int len;
	char *cleaned;

	len = ft_strlen(line) - count_ocurr(line, ' ');
	cleaned = malloc(sizeof(char) * len + 1);
	if (!cleaned)
		return (NULL);
	k = 0;
	i = 0;
	while (line[i])
	{
		if (ft_strchr(to_rm, line[i]) == NULL)
			cleaned[k++] = line[i];
		i++;
	}
	cleaned[k] = '\0';
	return (cleaned);
}

bool	char_found(char *str, char *searched)
{
	int len;
	int i;

	if (!str || !searched)
		return (false);
	len = ft_strlen(searched);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(str, searched[i]) != NULL)
			return (true);
		i++;
	}
	return (false);
}