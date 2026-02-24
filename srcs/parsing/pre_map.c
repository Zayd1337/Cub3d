#include "../../includes/cube3d.h"

bool	correct_texture(t_ctrl *ctrl, char *line)
{
	char	**tabl;
	int		flag_color;

	tabl = split_tab(line, " \t\n,");
	if (!tabl)
		return (ft_putstr_fd("malloc error\n", 1), false);
	if ((flag_color = set_color(ctrl, tabl)) == -1)
		return (free_tab(tabl), false);
	if (flag_color == 0 && set_texture(ctrl, tabl) == false)
		return (free_tab(tabl), false);
	return (free_tab(tabl), true);
}

bool	map_found(char *line)
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
		return (printf("Map found !\n"), true);
	return (false);
}

bool	set_config(t_ctrl *ctrl, int fd)
{
	char	*line;

	while ((line = get_next_line(fd)))
	{
		if ((ctrl->map->config_set == 6 && map_found(line)))
			break ;
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			continue ;
		}
		if (correct_texture(ctrl, line) == false)
			return (free(line), false);
		free(line);
	}
	if (ctrl->map->config_set < 6)
		return (ft_putstr_fd("Invalid number of config\n", 1), free(line),
			false);
	if (!(ctrl->map->map_stock = ft_strdup(line)))
		return (ft_putstr_fd("malloc error\n", 1), free(line), false);
	return (free(line), true);
}
