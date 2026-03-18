/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:50:23 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 15:15:48 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	correct_texture(t_ctrl *ctrl, char *line)
{
	char	**tabl;
	int		flag_color;

	tabl = split_tab(line, " \t\n,");
	if (!tabl)
		return ((ctrl->error = MALLOC), ctrl->error);
	flag_color = set_color(ctrl, tabl);
	if (flag_color == INVALID_CONFIG)
		return (free_tab(tabl), ctrl->error);
	if (flag_color == 0 && set_texture(ctrl, tabl) != SUCCES)
		return (free_tab(tabl), ctrl->error);
	return (free_tab(tabl), SUCCES);
}

bool	map_found(t_ctrl *ctrl, char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i] && ft_strchr(" ", line[i]) != NULL)
		i++;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		return (false);
	if (line[i] && ft_strchr("10EWSN", line[i]) != NULL)
	{
		ctrl->map->map_set = true;
		return (true);
	}
	return (false);
}

int	error_config(t_ctrl *ctrl)
{
	if (ctrl->map->colors_set + ctrl->map->textures_set < 6)
	{
		if (ctrl->map->map_set == true)
			return (MISSPLACED_ELEM);
		return (CONFIG_MISSING);
	}
	else if (ctrl->map->map_set == false)
	{
		if (ctrl->map->colors_set + ctrl->map->textures_set == 0)
			return (EMPTY_FILE);
		return (MAP_MISSING);
	}
	return (true);
}

static int	parse_config_line(t_ctrl *ctrl, char *line)
{
	int	all_set;

	all_set = (ctrl->map->colors_set + ctrl->map->textures_set == 6);
	if (map_found(ctrl, line) && all_set)
		return (1);
	if (ft_strcmp(line, "\n") == 0)
		return (SUCCES);
	if (correct_texture(ctrl, line) != SUCCES)
		return (ctrl->error);
	return (SUCCES);
}

int	set_config(t_ctrl *ctrl, int fd)
{
	char	*line;
	int		res;

	line = get_next_line(fd);
	while (line)
	{
		res = parse_config_line(ctrl, line);
		if (res == 1)
			break ;
		free(line);
		if (res != SUCCES)
			return (res);
		line = get_next_line(fd);
	}
	if (line)
	{
		ctrl->map->map_stock = ft_strdup(line);
		free(line);
		if (!ctrl->map->map_stock)
			return (ctrl->error = MALLOC, MALLOC);
	}
	return (SUCCES);
}
