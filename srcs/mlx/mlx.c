#include "../../includes/cube3d.h"

// void	free_struct_img()
// {

// }

bool	set_img(t_ctrl *ctrl)
{
	if ((ctrl->img.NO.img = mlx_xpm_file_to_image(ctrl->mlx,\
		ctrl->map->textures[0], &ctrl->img.dimension.x, \
		&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.NO.img = mlx_get_data_addr(ctrl->img.NO.img, &ctrl->img.NO.bpp, \
		&ctrl->img.NO.x_len, &ctrl->img.NO.endian)) == NULL)
		return (false);

	if ((ctrl->img.SO.img = mlx_xpm_file_to_image(ctrl->mlx,\
		ctrl->map->textures[1], &ctrl->img.dimension.x, \
		&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.SO.img = mlx_get_data_addr(ctrl->img.SO.img, &ctrl->img.SO.bpp, \
		&ctrl->img.SO.x_len, &ctrl->img.SO.endian)) == NULL)
		return (false);

	if ((ctrl->img.EA.img = mlx_xpm_file_to_image(ctrl->mlx,\
		ctrl->map->textures[2], &ctrl->img.dimension.x, \
		&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.EA.img = mlx_get_data_addr(ctrl->img.EA.img, &ctrl->img.EA.bpp, \
		&ctrl->img.EA.x_len, &ctrl->img.EA.endian)) == NULL)
		return (false);

	if ((ctrl->img.WE.img = mlx_xpm_file_to_image(ctrl->mlx,\
		ctrl->map->textures[3], &ctrl->img.dimension.x, \
		&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.WE.img = mlx_get_data_addr(ctrl->img.WE.img, &ctrl->img.WE.bpp, \
		&ctrl->img.WE.x_len, &ctrl->img.WE.endian)) == NULL)
		return (false);
	return (true);
}

int	end(t_ctrl *ctrl)
{
	// free_struct_img(ctrl);
	free_all(ctrl);
	exit(0);
	return (0);
}


int	keypress(int keysym, t_ctrl *ctrl)
{
	if (keysym == XK_Escape)
		end(ctrl);
	return (0);
}
