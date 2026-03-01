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
	if (type == '1' || type == ' ')
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
			fill_square(&ctrl->img.minimap, \
				give_color(ctrl->map->map[p.y][p.x]), ctrl->tile_size, p);
			p.x++;
		}
		p.y++;
	}
	return (SUCCES);
}

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



