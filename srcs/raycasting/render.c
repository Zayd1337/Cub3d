/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:55:03 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 17:55:28 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	fill_square(t_data *img, int color, int size, t_xy start)
{
	t_xy	pixel;

	if (color == -1)
		return ;
	pixel.y = start.y * size;
	while (pixel.y < start.y * size + size)
	{
		pixel.x = start.x * size;
		while (pixel.x < start.x * size + size)
		{
			my_mlx_pixel_put(img, pixel, img->img_dim, color);
			pixel.x++;
		}
		pixel.y++;
	}
}

static int	give_color(char type)
{
	if (type == '1' || type == ' ')
		return (0x4A489D);
	else
		return (0x21BB83);
}

static int	prepare_minimap(t_ctrl *ctrl)
{
	t_xy	p;

	p.y = 0;
	while (p.y < (int)ctrl->map->nb_line)
	{
		p.x = 0;
		while (p.x < (int)ctrl->map->len_line)
		{
			fill_square(&ctrl->img.minimap,
				give_color(ctrl->map->map[p.y][p.x]), ctrl->tile_size, p);
			p.x++;
		}
		p.y++;
	}
	return (SUCCES);
}

static int	prepare_background(t_ctrl *ctrl)
{
	t_xy	ind;
	int		sky_color;
	int		floor_color;
	int		current_color;

	sky_color = ctrl->map->color[1];
	floor_color = ctrl->map->color[0];
	ind.y = 0;
	while (ind.y < ctrl->img.f_c.img_dim.y)
	{
		ind.x = 0;
		if (ind.y < ctrl->img.f_c.img_dim.y / 2)
			current_color = sky_color;
		else
			current_color = floor_color;
		while (ind.x < ctrl->img.f_c.img_dim.x)
		{
			my_mlx_pixel_put(&ctrl->img.f_c, ind, ctrl->img.f_c.img_dim,
				current_color);
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
