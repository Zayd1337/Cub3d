#include "../../includes/cube3d.h"
#include <math.h>

int	tex_pixel(t_data *tex, int texX, int texY)
{
	char	*p;

	if (texX < 0) texX = 0;
	if (texX >= tex->img_dim.x) texX = tex->img_dim.x - 1;
	if (texY < 0) texY = 0;
	if (texY >= tex->img_dim.y) texY = tex->img_dim.y - 1;
	p = tex->addr + (texY * tex->x_len + texX * (tex->bpp / 8));
	return (*(unsigned int *)p);
}

void	put_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->img_dim.x || y < 0 || y >= img->img_dim.y)
		return ;
	dst = img->addr + (y * img->x_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_data	*choose_texture(t_ctrl *ctrl, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&ctrl->img.EA);
		return (&ctrl->img.WE);
	}
	if (ray->ray_dir_y > 0)
		return (&ctrl->img.SO);
	return (&ctrl->img.NO);
}

// Copie le fond precompute (F_C) dans to_print — plus rapide que put_pixel par pixel
void	draw_floor_and_ceiling(t_ctrl *ctrl)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		ft_memcpy(
			ctrl->img.to_print.addr + (y * ctrl->img.to_print.x_len),
			ctrl->img.F_C.addr + (y * ctrl->img.F_C.x_len),
			(size_t)ctrl->img.F_C.x_len);
		y++;
	}
}

int	render_frame(t_ctrl *ctrl)
{
	draw_floor_and_ceiling(ctrl);
	cast_rays(ctrl);
	return (SUCCES);
}
