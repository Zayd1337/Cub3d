#include "../../includes/cube3d.h"

int	set_texture(t_ctrl *ctrl, char **tabl)
{
	int			i;
	int			j;
	static char	*tex[4] = {"NO", "SO", "EA", "WE"};

	j = -1;
	while (tex[++j])
	{
		if (ft_strcmp(tabl[0], tex[j]))
			continue ;
		if (ctrl->map->textures[j] != NULL)
			return ((ctrl->error = INVALID_CONFIG), ctrl->error);
		i = 0;
		ctrl->map->textures[j] = ft_strdup(tabl[1]);
		if (!ctrl->map->textures[j])
			return ((ctrl->error = MALLOC), ctrl->error);
		ctrl->map->textures_set++;
		return (SUCCES);
	}
	// if (ctrl->map->colors_set + ctrl->map->textures_set < 6)
	// 	ctrl->error = CONFIG_MISSING;
	// else//pas supeeeer clean
	// 	ctrl->error = INVALID_CONFIG;
	return ((ctrl->error = error_config(ctrl)), ctrl->error);
}

bool	correct_RGB(t_ctrl *ctrl, char **tabl, int id)
{
	int	i;

	i = 0;
	while (tabl[++i])
	{
		if (ft_atoi(tabl[i]) < 0 || ft_atoi(tabl[i]) > 255)
			return (false);
		ctrl->map->color[id][i - 1] = ft_atoi(tabl[i]);
	}
	if (i < 4)
		return (false);
	ctrl->map->colors_set++;
	return (true);
}

int	set_color(t_ctrl *ctrl, char **tabl)
{
	int	type;
	int	i;

	type = -1;
	if (ft_strcmp(tabl[0], "F") == 0)
		type = 0;
	if (ft_strcmp(tabl[0], "C") == 0)
		type = 1;
	if (type == -1)
		return (0);
	i = -1;
	while (++i < 3)
	{
		if (ctrl->map->color[type][i] != -1)
			return ((ctrl->error = INVALID_CONFIG), ctrl->error);
	}
	if (correct_RGB(ctrl, tabl, type) == false)
		return ((ctrl->error = INVALID_CONFIG), ctrl->error);
	return (1);
}
