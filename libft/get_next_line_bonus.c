/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:01:09 by jeazil            #+#    #+#             */
/*   Updated: 2025/06/20 15:01:20 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_line(int fd, char *buffer, char *stock)
{
	int		check;
	char	*temp;

	check = 1;
	while (check > 0)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check == -1)
			return (free(stock), NULL);
		else if (check == 0)
			break ;
		buffer[check] = '\0';
		if (!stock)
			stock = ft_strdup("");
		temp = stock;
		stock = ft_strjoin(temp, buffer);
		if (!stock)
			return (NULL);
		free(temp);
		temp = NULL;
		if (tnt_strchr(buffer, '\n') != -1)
			break ;
	}
	return (stock);
}

static char	*fill_line(char *line)
{
	char	*stock;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[i + 1] == 0)
		return (NULL);
	stock = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!stock)
	{
		free(stock);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (stock);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*stock[MAX_FD];

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = read_line(fd, buffer, stock[fd]);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stock[fd] = fill_line(line);
	return (line);
}

/*int	main(void)
{
	int fd = open("pouet.txt", O_RDWR);
	int fd2 = open("pouet2.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd2));

	// char* s2 = get_next_line(fd);
	// char* s3 = get_next_line(fd);
	// char* s4 = get_next_line(fd);
	// char* s5 = get_next_line(fd);
	// char* s6 = get_next_line(fd);

	//printf("%s", s1);
	// printf("%s", s2);
	// printf("%s", s3);
	// printf("%s", s4);
	// printf("%s", s5);
	// printf("%s", s6);

	//free(s1);
	// free(s2);
	// free(s3);
	// free(s4);
	// free(s5);
	// free(s6);
}*/