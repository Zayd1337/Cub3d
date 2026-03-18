/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:34:39 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 17:34:52 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include <math.h>

int	tex_pixel(t_data *tex, int texX, int texY)
{
	char	*p;

	if (texX < 0)
		texX = 0;
	if (texX >= tex->img_dim.x)
		texX = tex->img_dim.x - 1;
	if (texY < 0)
		texY = 0;
	if (texY >= tex->img_dim.y)
		texY = tex->img_dim.y - 1;
	p = tex->addr + (texY * tex->x_len + texX * (tex->bpp / 8));
	return (*(unsigned int *)p);
}

int	my_mlx_pixel_put(t_data *data, t_xy p, t_xy win_s, int color)
{
	char	*dst;

	if (p.x < 0 || p.x >= win_s.x || p.y < 0 || p.y >= win_s.y)
		return (MALLOC);
	dst = data->addr + (p.y * data->x_len + p.x * (data->bpp / 8));
	*(unsigned int *)dst = color;
	return (SUCCES);
}

t_data	*choose_texture(t_ctrl *ctrl, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&ctrl->img.ea);
		return (&ctrl->img.we);
	}
	if (ray->ray_dir_y > 0)
		return (&ctrl->img.so);
	return (&ctrl->img.no);
}

void	draw_floor_and_ceiling(t_ctrl *ctrl)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		ft_memcpy(ctrl->img.to_print.addr + (y * ctrl->img.to_print.x_len),
			ctrl->img.f_c.addr + (y * ctrl->img.f_c.x_len),
			(size_t)ctrl->img.f_c.x_len);
		y++;
	}
}

int	render_frame(t_ctrl *ctrl)
{
	draw_floor_and_ceiling(ctrl);
	cast_rays(ctrl);
	return (SUCCES);
}
