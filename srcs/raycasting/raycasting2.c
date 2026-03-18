/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:36:19 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 17:36:19 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include <math.h>

static void	init_dda_steps(t_ray *ray, double posx, double posy)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (posx - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - posx) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (posy - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - posy) * ray->delta_dist_y;
	}
}

void	perform_dda(t_ctrl *ctrl, t_ray *ray, t_coor pos)
{
	init_dda_steps(ray, pos.x, pos.y);
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y >= 0 && ray->map_y < (int)ctrl->map->nb_line
			&& ray->map_x >= 0 && ray->map_x < (int)ctrl->map->len_line
			&& ctrl->map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	compute_wall_projection(t_ray *ray, t_wall *wall, t_coor pos)
{
	int	line_height;

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - pos.x + (1 - ray->step_x) / 2.0)
			/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - pos.y + (1 - ray->step_y) / 2.0)
			/ ray->ray_dir_y;
	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	wall->line_height = line_height;
	wall->draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (wall->draw_end >= WIN_HEIGHT)
		wall->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		wall->wall_x = pos.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall->wall_x = pos.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall->wall_x -= floor(wall->wall_x);
}

static void	init_ray(t_ctrl *ctrl, t_ray *ray, t_coor pos,
		double cameraX)
{
	ray->ray_dir_x = ctrl->player.dir.x + ctrl->player.plane.x * cameraX;
	ray->ray_dir_y = ctrl->player.dir.y + ctrl->player.plane.y * cameraX;
	ray->map_x = (int)pos.x;
	ray->map_y = (int)pos.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void	cast_rays(t_ctrl *ctrl)
{
	t_coor	pos;
	t_ray	ray;
	t_wall	wall;
	int		x;

	pos.x = ctrl->player.precis.x / ctrl->tile_size;
	pos.y = ctrl->player.precis.y / ctrl->tile_size;
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(ctrl, &ray, pos, 2.0 * x / (double)WIN_WIDTH - 1.0);
		perform_dda(ctrl, &ray, pos);
		compute_wall_projection(&ray, &wall, pos);
		draw_wall_stripe(ctrl, x, &ray, &wall);
		x++;
	}
}
