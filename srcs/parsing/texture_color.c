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
	return ((ctrl->error = error_config(ctrl)), ctrl->error);
}

//donne le bon format couleur pour my_mlx_pixel_put() 
int	convert_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

bool	correct_RGB(t_ctrl *ctrl, char **tabl, int id)
{
	int	i;
	int nb;
	t_xy	rgb;

	i = 0;
	while (tabl[++i])
	{
		nb = ft_atoi(tabl[i]);
		if (nb < 0 || nb > 255)
			return (printf ("correcr rgb\n"), false);
		if (i == 1)
			rgb.x = nb;
		if (i == 2)
			rgb.y = nb;
		if (i == 3)
			rgb.z = nb;
	}
	ctrl->map->color[id] = convert_rgb(rgb.x, rgb.y, rgb.z);
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
	i = 0;
	while (tabl[i])
		i++;
	if (i != 4)
		return ((ctrl->error = INVALID_CONFIG), ctrl->error);
	i = -1;
	while (++i < 3)
	{
		if (ctrl->map->color[type] != -1)
			return ((ctrl->error = INVALID_CONFIG), ctrl->error);
	}
	if (correct_RGB(ctrl, tabl, type) == false)
		return ((ctrl->error = INVALID_CONFIG), ctrl->error);
	return (1);
}
