#include "../../includes/cube3d.h"

//dispatchers
bool	correct_texture(t_ctrl *ctrl, char *line)
{
	char **tabl;
	int flag_color;
	tabl = ft_split(line, ' ');
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
	int i;

	if (!line)
		return (false);
	i = 0;
	while (line[i] && ft_strchr(" \t", line[i]) != NULL)
		i++;
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) \
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (false);
	if (line[i] && ft_strchr("10EWSN", line[i]) != NULL)//ok pour FC
		return (printf ("Map found !\n"), true);
	return (false);
}

//dispatchers du fichier
bool	set_config(t_ctrl *ctrl, int fd)
{
	char *line;

	while ((line = get_next_line(fd)) && !map_found(line))//si !erreur && !eof
	{
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			continue ;
		}
		print_map_infos(ctrl);
		if (correct_texture(ctrl, line) == false)//defini textures
			return (free(line), false);
		free(line);
	}
	if (ctrl->map->config_set < 6)
		return (free(line), false);
	if (!(ctrl->map->map_stock = ft_strdup(line)))
		return (free(line), false);
	return (free(line), true);
}

//on laisse la fonction tourner jusqu'a ce que toutes les textures/couleurs soient definient
//ou qu'une erreur soit detectee, ce qui arrivera si la map n'est pas au bon endroit ou s'il manque.
