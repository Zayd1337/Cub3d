#include "../../includes/cube3d.h"

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
				ctrl->map->textures[2], &ctrl->img.EA.img_dim.x,
            &ctrl->img.EA.img_dim.y)) == NULL)
		return (false);
	if ((ctrl->img.EA.addr = mlx_get_data_addr(ctrl->img.EA.img,
				&ctrl->img.EA.bpp, &ctrl->img.EA.x_len,
				&ctrl->img.EA.endian)) == NULL)
		return (false);
	if ((ctrl->img.WE.img = mlx_xpm_file_to_image(ctrl->mlx,
				ctrl->map->textures[3], &ctrl->img.WE.img_dim.x,
            &ctrl->img.WE.img_dim.y)) == NULL)
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
				ctrl->map->textures[0], &ctrl->img.NO.img_dim.x,
            &ctrl->img.NO.img_dim.y)) == NULL)
		return (false);
	if ((ctrl->img.NO.addr = mlx_get_data_addr(ctrl->img.NO.img,
				&ctrl->img.NO.bpp, &ctrl->img.NO.x_len,
				&ctrl->img.NO.endian)) == NULL)
		return (false);
	if ((ctrl->img.SO.img = mlx_xpm_file_to_image(ctrl->mlx,
				ctrl->map->textures[1], &ctrl->img.SO.img_dim.x,
            &ctrl->img.SO.img_dim.y)) == NULL)
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
		return (false);
	return (true);
}

bool    walk(t_ctrl *ctrl)
{
    double  new_x;
    double  new_y;
    double  margin;
    bool    moved;

    moved = false;
    margin = 0.15;
    if (ctrl->key_press[0])
    {
        new_x = ctrl->player.precis.x + ctrl->player.dir.x * ctrl->move_speed;
        new_y = ctrl->player.precis.y + ctrl->player.dir.y * ctrl->move_speed;
        if (check_collision(ctrl, new_x + (ctrl->player.dir.x * margin), ctrl->player.precis.y))
            ctrl->player.precis.x = new_x;
        if (check_collision(ctrl, ctrl->player.precis.x, new_y + (ctrl->player.dir.y * margin)))
            ctrl->player.precis.y = new_y;
        moved = true;
    }
    if (ctrl->key_press[1])
    {
        new_x = ctrl->player.precis.x - ctrl->player.dir.x * ctrl->move_speed;
        new_y = ctrl->player.precis.y - ctrl->player.dir.y * ctrl->move_speed;
        if (check_collision(ctrl, new_x - (ctrl->player.dir.x * margin), ctrl->player.precis.y))
            ctrl->player.precis.x = new_x;
        if (check_collision(ctrl, ctrl->player.precis.x, new_y - (ctrl->player.dir.y * margin)))
            ctrl->player.precis.y = new_y;
        moved = true;
    }
    if (ctrl->key_press[2])
    {
        new_x = ctrl->player.precis.x + ctrl->player.dir.y * ctrl->move_speed;
        new_y = ctrl->player.precis.y - ctrl->player.dir.x * ctrl->move_speed;
        if (check_collision(ctrl, new_x - (ctrl->player.dir.y * margin), ctrl->player.precis.y))
            ctrl->player.precis.x = new_x;
        if (check_collision(ctrl, ctrl->player.precis.x, new_y + (ctrl->player.dir.x * margin)))
            ctrl->player.precis.y = new_y;
        moved = true;
    }
    if (ctrl->key_press[3])
    {
        new_x = ctrl->player.precis.x - ctrl->player.dir.y * ctrl->move_speed;
        new_y = ctrl->player.precis.y + ctrl->player.dir.x * ctrl->move_speed;
        if (check_collision(ctrl, new_x + (ctrl->player.dir.y * margin), ctrl->player.precis.y))
            ctrl->player.precis.x = new_x;
        if (check_collision(ctrl, ctrl->player.precis.x, new_y - (ctrl->player.dir.x * margin)))
            ctrl->player.precis.y = new_y;
        moved = true;
    }
    return (moved);
}

bool rotate(t_ctrl *ctrl)
{
    double  old_dir_x;
    double  old_plane_x;
    double  angle;

    if (!ctrl->key_press[4] && !ctrl->key_press[5])
        return (false);
    if (ctrl->key_press[4])
        angle = -ctrl->rot_speed;
    else
        angle = ctrl->rot_speed;
    old_dir_x = ctrl->player.dir.x;
    ctrl->player.dir.x = ctrl->player.dir.x * cos(angle) - ctrl->player.dir.y * sin(angle);
    ctrl->player.dir.y = old_dir_x * sin(angle) + ctrl->player.dir.y * cos(angle);

    old_plane_x = ctrl->player.plane.x;
    ctrl->player.plane.x = ctrl->player.plane.x * cos(angle) - ctrl->player.plane.y * sin(angle);
    ctrl->player.plane.y = old_plane_x * sin(angle) + ctrl->player.plane.y * cos(angle);

    return (true);
}

int	move(t_ctrl *ctrl)
{
	struct timeval	tv;
	long			time;
	double			frame_time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	frame_time = (time - ctrl->old_time) / 1000.0;
	ctrl->old_time = time;
	ctrl->move_speed = frame_time * MOVE_SPEED * ctrl->tile_size;
	ctrl->rot_speed = frame_time * ROT_SPEED;
	if (walk(ctrl) | rotate(ctrl))
		render(ctrl);
	return (0);
}

int keypress(int keysym, t_ctrl *ctrl)
{
    if (keysym == XK_Escape)
		end(ctrl);
    if (keysym == XK_w) 
		ctrl->key_press[0] = true;
	if (keysym == XK_s) 
		ctrl->key_press[1] = true;
    if (keysym == XK_a) 
		ctrl->key_press[2] = true;
    if (keysym == XK_d) 
		ctrl->key_press[3] = true;
	if (keysym == XK_Left)
		ctrl->key_press[4] = true;
	if (keysym == XK_Right)
		ctrl->key_press[5] = true;
    return (0);
}

int keyrelease(int keysym, t_ctrl *ctrl)
{
    if (keysym == XK_w) 
		ctrl->key_press[0] = false;
	 if (keysym == XK_s) 
		ctrl->key_press[1] = false;
    if (keysym == XK_a) 
		ctrl->key_press[2] = false;
    if (keysym == XK_d) 
		ctrl->key_press[3] = false;
	if (keysym == XK_Left)
		ctrl->key_press[4] = false;
	if (keysym == XK_Right)
		ctrl->key_press[5] = false;
    return (0);
}
