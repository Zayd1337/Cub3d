#include "../../includes/cube3d.h"

int	correct_texture(t_ctrl *ctrl, char *line)
{
	char	**tabl;
	int		flag_color;

	tabl = split_tab(line, " \t\n,");
	if (!tabl)
		return ((ctrl->error = MALLOC), ctrl->error);
	if ((flag_color = set_color(ctrl, tabl)) == INVALID_CONFIG)
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

int	error_config(t_ctrl *ctrl)//ameliorer?
{
	if (ctrl->map->colors_set + ctrl->map->textures_set < 6)
	{
		if (ctrl->map->map_set == true)
			return (MISSPLACED_ELEM);
		else if (ctrl->map->colors_set < 2)
			return (CONFIG_MISSING);
	}
	else if (ctrl->map->map_set == false)
	{
		if (ctrl->map->colors_set + ctrl->map->textures_set < 0)
			return (EMPTY_FILE);
		else
			return (MAP_MISSING);
	}
	return (true);
}

int	set_config(t_ctrl *ctrl, int fd)
{
	char	*line;

	while ((line = get_next_line(fd)))
	{
		if ((ctrl->map->colors_set + ctrl->map->textures_set == 6
				&& map_found(ctrl, line)))
			break ;
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			continue ;
		}
		if (correct_texture(ctrl, line) != SUCCES)
			return (free(line), ctrl->error);
		free(line);
	}
	if (line && !(ctrl->map->map_stock = ft_strdup(line)))
		return ((ctrl->error = MALLOC), ctrl->error);
	free(line);
	return (SUCCES);//!!! rigueur de l'assignation de error
}
