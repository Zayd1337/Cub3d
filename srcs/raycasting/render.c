#include "../../includes/cube3d.h"

void	fill_square(t_data *img, int color, int size, t_xy start)
{
	t_xy	pixel;

	if (color == -1)
		return ;
	pixel.y = start.y*size;
	while (pixel.y < start.y*size + size)
	{
		pixel.x = start.x*size;
		while (pixel.x < start.x*size + size)
		{
			my_mlx_pixel_put(img, pixel, img->img_dim, color);
			pixel.x++;
		}
		pixel.y++;
	}
}

int	give_color(char type)
{
	if (type == ' ')
		return (-1);
	if (type == '1')
		return (0x4A489D);
	else
		return (0x21BB83);
}

int	prepare_minimap(t_ctrl *ctrl)
{
	t_xy	p;
	// t_xy	offset;

	// offset.x = ctrl->img.minimap.x_len - ;
	p.y = 0;
	while (p.y < (int)ctrl->map->nb_line)
	{
		p.x = 0;
		while (p.x < (int)ctrl->map->len_line)
		{
			if (ctrl->map->map[p.y][p.x] != ' ')
				fill_square(&ctrl->img.minimap, \
					give_color(ctrl->map->map[p.y][p.x]), ctrl->tile_size, p);
			p.x++;
		}
		p.y++;
	}
	return (SUCCES);
}

// int	prepare_background(t_ctrl *ctrl)
// {
// 	t_xy ind;
// 	int color;

// 	ind.y = 0;
// 	while (ind.y < ctrl->img.F_C.img_dim.y)
// 	{
// 		ind.x = 0;
// 		while (ind.x < ctrl->img.F_C.img_dim.x)
// 		{
// 			color = ctrl->map->color[0];
// 			if (ind.y < ctrl->img.F_C.img_dim.y/2)
// 				color = ctrl->map->color[1];
// 			my_mlx_pixel_put(&ctrl->img.F_C, ind, ctrl->img.F_C.img_dim, color);
// 			ind.x++;
// 		}
// 		ind.y++;
// 	}
// 	return (SUCCES);
// }

int prepare_background(t_ctrl *ctrl)
{
    t_xy ind;
    int sky_color = ctrl->map->color[1];
    int floor_color = ctrl->map->color[0];

    ind.y = 0;
    while (ind.y < ctrl->img.F_C.img_dim.y)
    {
        ind.x = 0;
        int current_color = (ind.y < ctrl->img.F_C.img_dim.y / 2) ? sky_color : floor_color;
        while (ind.x < ctrl->img.F_C.img_dim.x)
        {
            my_mlx_pixel_put(&ctrl->img.F_C, ind, ctrl->img.F_C.img_dim, current_color);
            ind.x++;
        }
        ind.y++;
    }
    return (SUCCES);
}

int	prepare_static(t_ctrl *ctrl)
{
	if (prepare_background(ctrl) != SUCCES)
		return ((ctrl->error = MALLOC), ctrl->error);
	if (prepare_minimap(ctrl) != SUCCES)
		return ((ctrl->error = MALLOC), ctrl->error);
	return (SUCCES);
}

int	add_player(t_ctrl *ctrl, t_data *img)
{
	t_xy c;

	c.x = (int)ctrl->player.precis.x;
	c.y = (int)ctrl->player.precis.y;
	if (!img)
		return (MALLOC);
	my_mlx_pixel_put(img, c, ctrl->img.to_print.img_dim, 0xE32925);
	return (SUCCES);
}

//diviser 1 map 1 central
int render(t_ctrl *ctrl)
{
    int y;
	t_xy	offset;

	offset.x = WIN_WIDTH - 20 - ctrl->img.minimap.img_dim.x;
	offset.y = 20;
    y = 0;
    while (y < WIN_HEIGHT)
    {
        ft_memcpy(ctrl->img.to_print.addr + (y * ctrl->img.to_print.x_len), 
            ctrl->img.F_C.addr + (y * ctrl->img.F_C.x_len), 
            ctrl->img.F_C.x_len);
		if (y >= offset.y && y < offset.y + ctrl->img.minimap.img_dim.y)
        {
            int m_y = y - offset.y;
            char *dst = ctrl->img.to_print.addr + (y * ctrl->img.to_print.x_len) + (offset.x * 4);
            char *src = ctrl->img.minimap.addr + (m_y * ctrl->img.minimap.x_len);
            ft_memcpy(dst, src, ctrl->img.minimap.x_len);
        }
        y++;
    }
    mlx_put_image_to_window(ctrl->mlx, ctrl->win, ctrl->img.to_print.img, 0, 0);
    return (SUCCES);
}

// int minimap_render(t_ctrl *ctrl)
// {
//     int y;

//     y = 0;
//     while (y < (int)(ctrl->map->nb_line * ctrl->tile_size))
//     {
//         ft_memcpy(ctrl->img.to_print.addr + (y * ctrl->img.to_print.x_len), 
//             ctrl->img.minimap.addr + (y * ctrl->img.minimap.x_len), 
//             ctrl->img.minimap.x_len);
//         y++;
//     }
//     add_player(ctrl, &ctrl->img.to_print);
//     mlx_put_image_to_window(ctrl->mlx, ctrl->win, ctrl->img.to_print.img, 0, 0);
//     return (SUCCES);
// }

