#include "../../includes/cube3d.h"

bool	set_img2(t_ctrl *ctrl)
{
	if ((ctrl->img.EA.img = mlx_xpm_file_to_image(ctrl->mlx,
				ctrl->map->textures[2], &ctrl->img.dimension.x,
				&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.EA.addr = mlx_get_data_addr(ctrl->img.EA.img,
				&ctrl->img.EA.bpp, &ctrl->img.EA.x_len,
				&ctrl->img.EA.endian)) == NULL)
		return (false);
	if ((ctrl->img.WE.img = mlx_xpm_file_to_image(ctrl->mlx,
				ctrl->map->textures[3], &ctrl->img.dimension.x,
				&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.WE.addr = mlx_get_data_addr(ctrl->img.WE.img,
				&ctrl->img.WE.bpp, &ctrl->img.WE.x_len,
				&ctrl->img.WE.endian)) == NULL)
		return (false);
	return (true);
}

bool	set_img(t_ctrl *ctrl)
{
	if ((ctrl->img.NO.img = mlx_xpm_file_to_image(ctrl->mlx,
				ctrl->map->textures[0], &ctrl->img.dimension.x,
				&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.NO.addr = mlx_get_data_addr(ctrl->img.NO.img,
				&ctrl->img.NO.bpp, &ctrl->img.NO.x_len,
				&ctrl->img.NO.endian)) == NULL)
		return (false);
	if ((ctrl->img.SO.img = mlx_xpm_file_to_image(ctrl->mlx,
				ctrl->map->textures[1], &ctrl->img.dimension.x,
				&ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.SO.addr = mlx_get_data_addr(ctrl->img.SO.img,
				&ctrl->img.SO.bpp, &ctrl->img.SO.x_len,
				&ctrl->img.SO.endian)) == NULL)
		return (false);
	if (set_img2(ctrl) == false)
		return (false);
	return (true);
}

int	end(t_ctrl *ctrl)
{
	free_all(ctrl);
	exit(0);
	return (0);
}

// int	cam_mov(t_ctrl *ctrl)
// {

// }

// bool	can_mov(char **map, int i, int j)
// {
// 	if (map[j][i])
// 		return (true);
// 	return (false);
// }

int	player_mov(t_ctrl *ctrl, int keysym)
{
	int mv;

	mv = true;
	if (keysym == XK_w && ctrl->map->map[ctrl->player.y-1][ctrl->player.x] != '1')//avancer
		ctrl->player.y -= 1, printf("up\n");
	else if (keysym == XK_a && ctrl->map->map[ctrl->player.y][ctrl->player.x-1] != '1')//aller a gauche
		ctrl->player.x -= 1, printf("left\n");
	else if (keysym == XK_s && ctrl->map->map[ctrl->player.y+1][ctrl->player.x] != '1')//reculer
		ctrl->player.y += 1, printf("down\n");
	else if (keysym == XK_d && ctrl->map->map[ctrl->player.y][ctrl->player.x+1] != '1')//aller a droite
		ctrl->player.x += 1, printf("right\n");
	else
		mv = false;
	return (mv);
}

int	keypress(int keysym, t_ctrl *ctrl)
{
	if (keysym == XK_Escape)
		end(ctrl);
	// else if (keysym == XK_Right)
	// 	cam_mov();
	// else if (keysym == XK_Left)
	// 	cam_mov();
	else if (keysym == XK_w)//avancer
		player_mov(ctrl, keysym);
	else if (keysym == XK_a)//aller a gauche
		player_mov(ctrl, keysym);
	else if (keysym == XK_s)//reculer
		player_mov(ctrl, keysym);
	else if (keysym == XK_d)//aller a droite
		player_mov(ctrl, keysym);
	return (0);
}
