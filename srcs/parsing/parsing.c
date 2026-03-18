/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:24:45 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/18 09:42:19 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_mapname(char *file_name)
{
	int	len;

	if (!file_name)
		return (INVALID_FILE);
	len = ft_strlen(file_name);
	if (len < 5)
		return (INVALID_FILE);
	if (ft_strncmp(file_name + (len - 4), ".cub", 4) == 0)
		return (SUCCES);
	return (INVALID_FILE);
}

int	set_map(t_ctrl *ctrl, int fd)
{
	ctrl->error = fill_temp_map(ctrl, fd);
	if (ctrl->error != SUCCES)
		return (ctrl->error);
	ctrl->error = convert_in_tab(ctrl);
	if (ctrl->error != SUCCES)
		return (ctrl->error);
	return (SUCCES);
}

int	check_file(char *name)
{
	int		fd;
	char	c;

	if (!name)
		return (-1);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (INVALID_FILE);
	if (read(fd, &c, 0) < 0)
		return (close(fd), INVALID_FILE);
	return (fd);
}

int	texture_file_exist(t_ctrl *ctrl)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		fd = check_file(ctrl->map->textures[i]);
		if (fd == -1)
		{
			free(ctrl->map->map_stock);
			ctrl->error = INVALID_FILE;
			return (ctrl->error);
		}
		close(fd);
		i++;
	}
	return (SUCCES);
}

int	parse_data(t_ctrl *ctrl, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return ((ctrl->error = INVALID_INPUT), ctrl->error);
	if (check_mapname(argv[1]) != SUCCES)
		return ((ctrl->error = INVALID_FILE), ctrl->error);
	fd = check_file(argv[1]);
	if (fd == INVALID_FILE)
		return ((ctrl->error = INVALID_FILE), ctrl->error);
	if (init_map(ctrl, argv[1]) != SUCCES)
		return (close(fd), ctrl->error);
	if (set_config(ctrl, fd) != SUCCES)
		return (close(fd), ctrl->error);
	if (texture_file_exist(ctrl) != SUCCES)
		return (close(fd), ctrl->error);
	if (set_map(ctrl, fd) != SUCCES)
		return (close(fd), ctrl->error);
	if (parse_map(ctrl) != SUCCES)
		return (close(fd), ctrl->error);
	return (close(fd), SUCCES);
}
