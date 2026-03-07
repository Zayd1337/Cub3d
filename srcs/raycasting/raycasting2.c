#include "../../includes/cube3d.h"
#include <math.h>

static void	init_dda_steps(t_ray *ray, double posX, double posY)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (posX - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - posX) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (posY - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - posY) * ray->delta_dist_y;
	}
}

// Parcourir la grille jusqu’à un mur (hit).
void	perform_dda(t_ctrl *ctrl, t_ray *ray, double posX, double posY)
{
	init_dda_steps(ray, posX, posY);
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

void	compute_wall_projection(t_ray *ray, t_wall *wall,
		double posX, double posY)
{
	int	lineHeight;

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - posX
				+ (1 - ray->step_x) / 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - posY
				+ (1 - ray->step_y) / 2.0) / ray->ray_dir_y;
	lineHeight = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	wall->line_height = lineHeight;
	wall->draw_start = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = lineHeight / 2 + WIN_HEIGHT / 2;
	if (wall->draw_end >= WIN_HEIGHT)
		wall->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		wall->wall_x = posY + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall->wall_x = posX + ray->perp_wall_dist * ray->ray_dir_x;
	wall->wall_x -= floor(wall->wall_x);
}

static void	init_ray(t_ctrl *ctrl, t_ray *ray,
		double posX, double posY, double cameraX)
{
	ray->ray_dir_x = ctrl->player.dir.x + ctrl->player.plane.x * cameraX;
	ray->ray_dir_y = ctrl->player.dir.y + ctrl->player.plane.y * cameraX;
	ray->map_x = (int)posX;
	ray->map_y = (int)posY;
	ray->delta_dist_x = (ray->ray_dir_x == 0)
		? 1e30 : fabs(1.0 / ray->ray_dir_x);
	ray->delta_dist_y = (ray->ray_dir_y == 0)
		? 1e30 : fabs(1.0 / ray->ray_dir_y);
}

// un rayon par colonne
void	cast_rays(t_ctrl *ctrl)
{
	double	posX;
	double	posY;
	t_ray	ray;
	t_wall	wall;
	int		x;

	posX = ctrl->player.precis.x / ctrl->tile_size;
	posY = ctrl->player.precis.y / ctrl->tile_size;
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(ctrl, &ray, posX, posY, 2.0 * x / (double)WIN_WIDTH - 1.0);
		perform_dda(ctrl, &ray, posX, posY);
		compute_wall_projection(&ray, &wall, posX, posY);
		draw_wall_stripe(ctrl, x, &ray, &wall);
		x++;
	}
}
