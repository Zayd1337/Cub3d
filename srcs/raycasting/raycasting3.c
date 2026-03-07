#include "../../includes/cube3d.h"
#include <math.h>

static void	init_tex_coords(t_wall *wall, t_data *tex, t_ray *ray)
{
	wall->tex_x = (int)(wall->wall_x * tex->img_dim.x);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		wall->tex_x = tex->img_dim.x - wall->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		wall->tex_x = tex->img_dim.x - wall->tex_x - 1;
	wall->step = (double)tex->img_dim.y / wall->line_height;
	wall->tex_pos = (wall->draw_start - WIN_HEIGHT / 2
			+ wall->line_height / 2.0) * wall->step;
}

static void	draw_column(t_ctrl *ctrl, t_data *tex, int x, t_wall *wall,
		t_ray *ray)
{
	int	y;
	int	texY;
	int	color;

	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		texY = (int)wall->tex_pos;
		if (texY < 0)
			texY = 0;
		if (texY >= tex->img_dim.y)
			texY = tex->img_dim.y - 1;
		wall->tex_pos += wall->step;
		color = tex_pixel(tex, wall->tex_x, texY);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&ctrl->img.to_print, x, y, color);
		y++;
	}
}

void	draw_wall_stripe(t_ctrl *ctrl, int x, t_ray *ray, t_wall *wall)
{
	t_data	*tex;

	if (wall->line_height == 0 || wall->draw_start > wall->draw_end)
		return ;
	tex = choose_texture(ctrl, ray);
	if (!tex || tex->img_dim.y <= 0 || tex->img_dim.x <= 0)
		return ;
	init_tex_coords(wall, tex, ray);
	draw_column(ctrl, tex, x, wall, ray);
}
