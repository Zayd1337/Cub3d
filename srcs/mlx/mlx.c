#include "../../includes/cube3d.h"

// //donne la couleur color au pixel (x,y)
//p sont les coordonnees du pixel qu'on veut remplir
//win_s window_size = taille de l'image ou on ecrit
int	my_mlx_pixel_put(t_data *data, t_xy p, t_xy win_s, int color)
{
	char	*dst;

	if (p.x < 0 || p.x >= win_s.x || p.y < 0 || p.y >= win_s.y)
		return (MALLOC); 
	dst = data->addr + (p.y * data->x_len + p.x * (data->bpp / 8));
	*(unsigned int*)dst = color;
	return (SUCCES);
}

bool	set_img2(t_ctrl *ctrl)
{
	if ((ctrl->img.EA.img = mlx_xpm_file_to_image(ctrl->mlx,
				ctrl->map->textures[2], &ctrl->img.dimension.x,
				&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.EA.addr = mlx_get_data_addr(ctrl->img.EA.img,
				&ctrl->img.EA.bpp, &ctrl->img.EA.x_len,
				&ctrl->img.EA.endian)) == NULL)
		return (false);
	if ((ctrl->img.WE.img = mlx_xpm_file_to_image(ctrl->mlx,
				ctrl->map->textures[3], &ctrl->img.dimension.x,
				&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.WE.addr = mlx_get_data_addr(ctrl->img.WE.img,
				&ctrl->img.WE.bpp, &ctrl->img.WE.x_len,
				&ctrl->img.WE.endian)) == NULL)
		return (false);
	ctrl->img.F_C.img_dim.x = WIN_WIDTH;
	ctrl->img.F_C.img_dim.y = WIN_HEIGHT;
	if ((ctrl->img.F_C.img = mlx_new_image(ctrl->mlx, ctrl->img.F_C.img_dim.x,
				ctrl->img.F_C.img_dim.y)) == NULL)
		return (false);
	if ((ctrl->img.F_C.addr = mlx_get_data_addr(ctrl->img.F_C.img,
				&ctrl->img.F_C.bpp, &ctrl->img.F_C.x_len,
				&ctrl->img.F_C.endian)) == NULL)
		return (false);
	ctrl->img.minimap.img_dim.x = ctrl->map->len_line*ctrl->tile_size;
	ctrl->img.minimap.img_dim.y = ctrl->map->nb_line*ctrl->tile_size;
	if ((ctrl->img.minimap.img = mlx_new_image(ctrl->mlx, ctrl->img.minimap.img_dim.x,
				ctrl->img.minimap.img_dim.y)) == NULL)
		return (false);
	if ((ctrl->img.minimap.addr = mlx_get_data_addr(ctrl->img.minimap.img,
				&ctrl->img.minimap.bpp, &ctrl->img.minimap.x_len,
				&ctrl->img.minimap.endian)) == NULL)
		return (false);
	// ctrl->img.player.img_dim.x = ctrl->tile_size*ctrl->map->len_line;
	// ctrl->img.player.img_dim.y = ctrl->tile_size*ctrl->map->nb_line;
	// if ((ctrl->img.player.img = mlx_new_image(ctrl->mlx, ctrl->img.player.img_dim.x,
	// 			ctrl->img.player.img_dim.y)) == NULL)
	// 	return (false);
	// if ((ctrl->img.player.addr = mlx_get_data_addr(ctrl->img.player.img,
	// 			&ctrl->img.player.bpp, &ctrl->img.player.x_len,
	// 			&ctrl->img.player.endian)) == NULL)
	// 	return (false);
	ctrl->img.to_print.img_dim.x = WIN_WIDTH;
	ctrl->img.to_print.img_dim.y = WIN_HEIGHT;
	if ((ctrl->img.to_print.img = mlx_new_image(ctrl->mlx, WIN_WIDTH, WIN_HEIGHT)) == NULL)
		return (false);
	if ((ctrl->img.to_print.addr = mlx_get_data_addr(ctrl->img.to_print.img,
				&ctrl->img.to_print.bpp, &ctrl->img.to_print.x_len,
				&ctrl->img.to_print.endian)) == NULL)
		return (false);
	return (true);
}

bool	set_img(t_ctrl *ctrl)
{
	if ((ctrl->img.NO.img = mlx_xpm_file_to_image(ctrl->mlx,
				ctrl->map->textures[0], &ctrl->img.dimension.x,
				&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.NO.addr = mlx_get_data_addr(ctrl->img.NO.img,
				&ctrl->img.NO.bpp, &ctrl->img.NO.x_len,
				&ctrl->img.NO.endian)) == NULL)
		return (false);
	if ((ctrl->img.SO.img = mlx_xpm_file_to_image(ctrl->mlx,
				ctrl->map->textures[1], &ctrl->img.dimension.x,
				&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.SO.addr = mlx_get_data_addr(ctrl->img.SO.img,
				&ctrl->img.SO.bpp, &ctrl->img.SO.x_len,
				&ctrl->img.SO.endian)) == NULL)
		return (false);
	if (set_img2(ctrl) == false)
		return (false);
	return (true);
}

int	end(t_ctrl *ctrl)
{
	free_all(ctrl);
	exit(0);
	return (0);
}

bool	check_collision(t_ctrl *ctrl, double next_x, double next_y)
{
	t_xy xy;

	if (!ctrl->map || !ctrl->map->map)
		return (printf("map doesn't exist\n"), false);
	xy.x = (int)next_x/ctrl->tile_size;
	xy.y = (int)next_y/ctrl->tile_size;
	if (ctrl->map->map[xy.y][xy.x] == '1')
		return (printf("wall detected\n"), false);
	return (true);
}

int move(t_ctrl *ctrl)
{
    double move_x = 0;
    double move_y = 0;
	t_coor next;

    if (ctrl->key_press[0]) 
		move_y -= SPEED; // W
    if (ctrl->key_press[2]) 
		move_y += SPEED; // S
    if (ctrl->key_press[1]) 
		move_x -= SPEED; // A
    if (ctrl->key_press[3]) 
		move_x += SPEED; // D
    if (move_x == 0 && move_y == 0)
        return (0);
    
    next.x = ctrl->player.precis.x + move_x;
    next.y = ctrl->player.precis.y + move_y;
    if (check_collision(ctrl, next.x, next.y))
    {
        ctrl->player.precis = next;
		printf ("move\n");
        render(ctrl);
    }
    return (0);
}

int keypress(int keysym, t_ctrl *ctrl)
{
    if (keysym == XK_Escape)
		end(ctrl);
    if (keysym == XK_w) 
		ctrl->key_press[0] = true;
    if (keysym == XK_a) 
		ctrl->key_press[1] = true;
    if (keysym == XK_s) 
		ctrl->key_press[2] = true;
    if (keysym == XK_d) 
		ctrl->key_press[3] = true;
    return (0);
}

int keyrelease(int keysym, t_ctrl *ctrl)
{
    if (keysym == XK_w) 
		ctrl->key_press[0] = false;
    if (keysym == XK_a) 
		ctrl->key_press[1] = false;
    if (keysym == XK_s) 
		ctrl->key_press[2] = false;
    if (keysym == XK_d) 
		ctrl->key_press[3] = false;
    return (0);
}
