#include "../../includes/cube3d.h"

//verifie si la texture donnee est correct et unique puis la set dans la struct map
bool set_texture(t_ctrl *ctrl, char **tabl)
{
	int i;
	int j = 0;
	static char *tex[4] = {"NO", "SO", "EA", "WE"};

	while (tex[j])
	{
		if (ft_strcmp(tabl[0], tex[j]))
		{
			j++;
			continue;
		}
		if (ctrl->map->textures[j] != NULL)
			return (ft_putstr_fd(tex[j], 1), ft_putstr_fd(" identifier already used\n", 1), false);
		i = 0;
		while (ctrl->map->textures[i] && i < 4)
		{
			if (!ft_strcmp(tabl[1], ctrl->map->textures[i]))
				return (ft_putstr_fd(tabl[1], 1), ft_putstr_fd(" texture already used\n", 1), false);
			i++;
		}
		ctrl->map->textures[j] = remove_chars(tabl[1], "\n \t");
		ctrl->map->config_set++;
		return (true);
		j++;
	}
	return (ft_putstr_fd(tabl[0], 1), ft_putstr_fd(" is an invalid identifier\n", 1), false);
}


bool	correct_RGB(t_ctrl *ctrl, char *line, int id)
{
	char **rgb;
	char *clean_l;
	int i;
	
	clean_l = remove_chars(line, " ");//on a une ligne sans " "
	if (!clean_l)
		return (false);
	rgb = ft_split(clean_l, ',');
	if (!rgb)
		return (false);
	i = 0;
	while (rgb[i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (free(clean_l), free_tab(rgb), false);
		ctrl->map->color[id][i] = ft_atoi(rgb[i]);
		i++;
	}
	ctrl->map->config_set++;
	return (free(clean_l), free_tab(rgb), true);
}

//return 1 si ct une couleur, 0 si c'en etait pas une et -1 si erreur
int	set_color(t_ctrl *ctrl, char **tabl)
{
	if (!ft_strcmp(tabl[0], "F"))
	{
		if (ctrl->map->color[0][0] != -1 && ctrl->map->color[0][1] != -1 && ctrl->map->color[0][2] != -1)
			return (ft_putstr_fd(tabl[0], 1), ft_putstr_fd(" identifier already allocated\n", 1), -1);
		if (correct_RGB(ctrl, tabl[1], 0) == false)
			return (ft_putstr_fd(tabl[1], 1), ft_putstr_fd(" : invalid RGB\n", 1), -1);
		return (1);
	}
	if (!ft_strcmp(tabl[0], "C"))
	{
		if (ctrl->map->color[1][0] != -1 && ctrl->map->color[1][1] != -1 && ctrl->map->color[1][2] != -1)
			return (ft_putstr_fd(tabl[0], 1), ft_putstr_fd(" identifier already allocated\n", 1), -1);
		if (correct_RGB(ctrl, tabl[1], 1) == false)
			return (ft_putstr_fd(tabl[1], 1), ft_putstr_fd(" : invalid RGB\n", 1), -1);
		return (1);
	}
	return (0);
}