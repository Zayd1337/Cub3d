#include "../../includes/cube3d.h"

bool	set_tile_size(t_ctrl *ctrl)//ici on choisi la taille des unites de la minimap
{
	t_xy screen_size;

	if (ctrl->map->len_line == 0 || ctrl->map->nb_line == 0)
    	return (false);
	// mlx_get_screen_size(ctrl->mlx, &screen_size.x, &screen_size.y);
	screen_size.x = WIN_WIDTH/4 / ctrl->map->len_line;
	screen_size.y = WIN_HEIGHT/4 / ctrl->map->nb_line;

	ctrl->tile_size = screen_size.x;
	if (screen_size.y < screen_size.x)
		ctrl->tile_size = screen_size.y;
	printf ("tile size : %d x %d\n", ctrl->tile_size, ctrl->tile_size);
	printf ("So the map size is %lu x %lu pixels\n", ctrl->map->len_line*ctrl->tile_size, ctrl->map->nb_line*ctrl->tile_size);
	return (true);
}

int	init_minilibx(t_ctrl *ctrl)
{
	ctrl->mlx = mlx_init();
	if (!ctrl->mlx)
		return ((ctrl->error = MALLOC), ctrl->error);
	set_tile_size(ctrl);
	//1ere position du player
	ctrl->player.precis.x = ctrl->player.map_c.x*ctrl->tile_size + ctrl->tile_size/2;
	ctrl->player.precis.y = ctrl->player.map_c.y*ctrl->tile_size + ctrl->tile_size/2;
	printf ("map[%d][%d], pix_coor : [%f][%f]\n", ctrl->player.map_c.y, ctrl->player.map_c.x, ctrl->player.precis.y, ctrl->player.precis.x);
	ctrl->win = mlx_new_window(ctrl->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!ctrl->win)
		return ((ctrl->error = MALLOC), ctrl->error);
	// ctrl->minimap_size.x = ctrl->map->len_line*ctrl->tile_size;
	if (set_img(ctrl) == false)
		return ((ctrl->error = MALLOC), ctrl->error);
	return (SUCCES);
}

void	init_textures_colors(t_map *map)
{
	map->color[0] = -1;
	map->color[1] = -1;
	map->textures[0] = NULL;
	map->textures[1] = NULL;
	map->textures[2] = NULL;
	map->textures[3] = NULL;
}

int	init_map(t_ctrl *ctrl, char *name)
{
	ctrl->map = malloc(sizeof(t_map));
	if (!ctrl->map)
		return ((ctrl->error = MALLOC), ctrl->error);
	if (name)
	{
		ctrl->map->name = ft_strdup(name);
		if (!ctrl->map->name)
			return ((ctrl->error = MALLOC), ctrl->error);
	}
	ctrl->map->temp_map = NULL;
	ctrl->map->map_stock = NULL;
	ctrl->map->map = NULL;
	ctrl->map->nb_line = 0;
	ctrl->map->len_line = 0;
	ctrl->map->colors_set = 0;
	ctrl->map->textures_set = 0;
	ctrl->map->map_set = false;
	ctrl->map->orientation = -1;
	init_textures_colors(ctrl->map);
	return (SUCCES);
}

void	init_struct(t_ctrl *ctrl)
{
	int i;

	ctrl->error = SUCCES;
	ctrl->map = NULL;
	ctrl->win = NULL;
	ctrl->mlx = NULL;
	i = 0;
	while (i < 6)
		ctrl->key_press[i++] = false;
	ctrl->img.NO.img = NULL;
	ctrl->img.SO.img = NULL;
	ctrl->img.EA.img = NULL;
	ctrl->img.WE.img = NULL;
	ctrl->img.F_C.img = NULL;
	ctrl->img.minimap.img = NULL;
	ctrl->img.to_print.img = NULL;
}
