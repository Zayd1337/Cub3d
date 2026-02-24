#include "../../includes/cube3d.h"

bool	set_texture(t_ctrl *ctrl, char **tabl)
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
			return (ft_putstr_fd(tex[j], 1),
				ft_putstr_fd(" identifier already used\n", 1), false);
		i = 0;
		ctrl->map->textures[j] = ft_strdup(tabl[1]);
		ctrl->map->config_set++;
		return (true);
	}
	return (ft_putstr_fd(tabl[0], 1),
		ft_putstr_fd(" is an invalid identifier\n", 1), false);
}

bool	correct_RGB(t_ctrl *ctrl, char **tabl, int id)
{
	int	i;

	i = 1;
	while (tabl[i])
	{
		if (ft_atoi(tabl[i]) < 0 || ft_atoi(tabl[i]) > 255)
			return (false);
		ctrl->map->color[id][i - 1] = ft_atoi(tabl[i]);
		i++;
	}
	ctrl->map->config_set++;
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
			return (ft_putstr_fd(tabl[0], 1),
				ft_putstr_fd(" identifier already allocated\n", 1), -1);
	}
	if (correct_RGB(ctrl, tabl, type) == false)
		return (ft_putstr_fd(tabl[1], 1), ft_putstr_fd(" : invalid RGB\n", 1),
			-1);
	return (1);
}
