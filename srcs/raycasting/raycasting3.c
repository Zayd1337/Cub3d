/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:53:04 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 17:53:04 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include <math.h>

t_data	*init_tex_coords(t_ctrl *ctrl, t_wall *wall, t_ray *ray)
{
	t_data	*tex;

	if (wall->line_height == 0 || wall->draw_start > wall->draw_end)
		return (NULL);
	tex = choose_texture(ctrl, ray);
	if (!tex || tex->img_dim.y <= 0 || tex->img_dim.x <= 0)
		return (NULL);
	wall->tex_x = (int)(wall->wall_x * tex->img_dim.x);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		wall->tex_x = tex->img_dim.x - wall->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		wall->tex_x = tex->img_dim.x - wall->tex_x - 1;
	wall->step = (double)tex->img_dim.y / wall->line_height;
	wall->tex_pos = (wall->draw_start - WIN_HEIGHT / 2 + wall->line_height
			/ 2.0) * wall->step;
	return (tex);
}

static void	put_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->img_dim.x || y < 0 || y >= img->img_dim.y)
		return ;
	dst = img->addr + (y * img->x_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_wall_stripe(t_ctrl *ctrl, int x, t_ray *ray, t_wall *wall)
{
	t_data	*tex;
	int		y;
	int		tex_y;
	int		color;

	tex = init_tex_coords(ctrl, wall, ray);
	if (!tex)
		return ;
	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		tex_y = (int)wall->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->img_dim.y)
			tex_y = tex->img_dim.y - 1;
		wall->tex_pos += wall->step;
		color = tex_pixel(tex, wall->tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&ctrl->img.to_print, x, y, color);
		y++;
	}
}
