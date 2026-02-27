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

	p.y = 0;
	while (p.y < (int)ctrl->map->nb_line)
	{
		p.x = 0;
		while (p.x < (int)ctrl->map->len_line)
		{
			// printf("pixel[%d][%d]\n", p.y, p.x);
			if (ctrl->map->map[p.y][p.x] != ' ')
				fill_square(&ctrl->img.minimap, \
					give_color(ctrl->map->map[p.y][p.x]), ctrl->tile_size, p);
			p.x++;
		}
		p.y++;
	}
	//!securite a ajouter!
	// mlx_put_image_to_window(ctrl->mlx, ctrl->win, ctrl->img.minimap.img, 0, 0);
	return (SUCCES);
}

int	prepare_static(t_ctrl *ctrl)
{
	//init des truc qui ne seront pas modifies, juste copies a la rigueur

	// if (prepare_floor_ceiling(&ctrl) != SUCCES)
	// 	return (print_error(&ctrl), free_all(&ctrl), 1);
	if (prepare_minimap(ctrl) != SUCCES)
		return (print_error(ctrl), free_all(ctrl), 1);
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

int render(t_ctrl *ctrl)
{
    int y;

    y = 0;
    while (y < (int)(ctrl->map->nb_line * ctrl->tile_size))
    {
        ft_memcpy(ctrl->img.to_print.addr + (y * ctrl->img.to_print.x_len), 
            ctrl->img.minimap.addr + (y * ctrl->img.minimap.x_len), 
            ctrl->img.minimap.x_len);
        y++;
    }
    add_player(ctrl, &ctrl->img.to_print);
    mlx_put_image_to_window(ctrl->mlx, ctrl->win, ctrl->img.to_print.img, 0, 0);
    return (SUCCES);
}

