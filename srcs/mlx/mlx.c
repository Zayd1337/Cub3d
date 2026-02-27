#include "../../includes/cube3d.h"

// //donne la couleur color au pixel (x,y)
//p sont les coordonnees du pixel qu'on veut remplir
//win_s window_size = taille de l'image ou on ecrit
void	my_mlx_pixel_put(t_data *data, t_xy p, t_xy win_s, int color)
{
	char	*dst;

	// printf ("win size : %dx%d\n", win_s.x, win_s.y);
	if (p.x < 0 || p.x >= win_s.x || p.y < 0 || p.y >= win_s.y)
		return ; 
	// printf("%d, %d\n", win_s.x, win_s.y);
	//On decale au pixel (x,y)
	dst = data->addr + (p.y * data->x_len + p.x * (data->bpp / 8));
	//on colore le pixel trouve 
	*(unsigned int*)dst = color;
}

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
	if ((ctrl->img.F_C.img = mlx_new_image(ctrl->mlx, ctrl->img.dimension.x,
				ctrl->img.dimension.y)) == NULL)
		return (false);
	if ((ctrl->img.F_C.addr = mlx_get_data_addr(ctrl->img.F_C.img,
				&ctrl->img.F_C.bpp, &ctrl->img.F_C.x_len,
				&ctrl->img.F_C.endian)) == NULL)
		return (false);
	ctrl->img.minimap.img_dim.x = ctrl->map->len_line*ctrl->tile_size;
	ctrl->img.minimap.img_dim.y = ctrl->map->nb_line*ctrl->tile_size;
	if ((ctrl->img.minimap.img = mlx_new_image(ctrl->mlx, ctrl->img.minimap.img_dim.x,
				ctrl->img.minimap.img_dim.y)) == NULL)
		return (false);
	if ((ctrl->img.minimap.addr = mlx_get_data_addr(ctrl->img.minimap.img,
				&ctrl->img.minimap.bpp, &ctrl->img.minimap.x_len,
				&ctrl->img.minimap.endian)) == NULL)
		return (false);
	// ctrl->img.player.img_dim.x = ctrl->tile_size*ctrl->map->len_line;
	// ctrl->img.player.img_dim.y = ctrl->tile_size*ctrl->map->nb_line;
	// if ((ctrl->img.player.img = mlx_new_image(ctrl->mlx, ctrl->img.player.img_dim.x,
	// 			ctrl->img.player.img_dim.y)) == NULL)
	// 	return (false);
	// if ((ctrl->img.player.addr = mlx_get_data_addr(ctrl->img.player.img,
	// 			&ctrl->img.player.bpp, &ctrl->img.player.x_len,
	// 			&ctrl->img.player.endian)) == NULL)
	// 	return (false);
	ctrl->img.to_print.img_dim.x = ctrl->img.minimap.img_dim.x;
	ctrl->img.to_print.img_dim.y = ctrl->img.minimap.img_dim.y;
	if ((ctrl->img.to_print.img = mlx_new_image(ctrl->mlx, WIN_WIDTH, WIN_HEIGHT)) == NULL)
		return (false);
	if ((ctrl->img.to_print.addr = mlx_get_data_addr(ctrl->img.to_print.img,
				&ctrl->img.to_print.bpp, &ctrl->img.to_print.x_len,
				&ctrl->img.to_print.endian)) == NULL)
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

int player_mov(t_ctrl *ctrl, int keysym)
{
    double step = 1;
	t_coor next;
	t_xy tile;

    next.x = ctrl->player.precis.x;
    next.y = ctrl->player.precis.y;

    if (keysym == XK_w)// avancer
        next.y -= step;
    else if (keysym == XK_s)// reculer
        next.y += step;
    else if (keysym == XK_a) // gauche
        next.x -= step;
    else if (keysym == XK_d)// Droite
        next.x += step;
    else
		return (false);
	tile.x = (int)next.x/ctrl->tile_size;
	tile.y = (int)next.y/ctrl->tile_size;
	printf ("test map[%d][%d]\n", tile.y, tile.x);
    if (ctrl->map->map[tile.y][tile.x] != '1')
    {
        ctrl->player.precis.x = next.x;
        ctrl->player.precis.y = next.y;
		ctrl->player.map_c.x = tile.x;
        ctrl->player.map_c.y = tile.y;
		if (render(ctrl) != SUCCES)
			return (false);
        return (true);
    }
    return (printf("move impossible\n"), false);
}

// // Exemple de correction dans player_mov
// void player_mov(t_ctrl *ctrl, double new_x, double new_y)
// {
//     int map_x = (int)(new_x / ctrl->tile_size);
//     int map_y = (int)(new_y / ctrl->tile_size);

//     if (map_y >= 0 && map_y < (int)ctrl->map->nb_line && 
//         map_x >= 0 && map_x < (int)ctrl->map->len_line)
//     {
//         if (ctrl->map->map[map_y][map_x] != '1')
//         {
//             ctrl->p_player.x = new_x;
//             ctrl->p_player.y = new_y;
//         }
//         else
//             printf("Collision avec un mur à la case [%d][%d]\n", map_y, map_x);
//     }
//     else
//         printf("Tentative de sortie de map à [%d][%d]\n", map_y, map_x);
// }

// int	player_mov(t_ctrl *ctrl, int keysym)
// {
// 	int mv;

// 	mv = true;
// 	if (keysym == XK_w && ctrl->map->map[ctrl->p_player.y-1][ctrl->p_player.x] != '1')//avancer
// 		ctrl->p_player.y -= 1, printf("up\n");
// 	else if (keysym == XK_a && ctrl->map->map[ctrl->p_player.y][ctrl->p_player.x-1] != '1')//aller a gauche
// 		ctrl->p_player.x -= 1, printf("left\n");
// 	else if (keysym == XK_s && ctrl->map->map[ctrl->p_player.y+1][ctrl->p_player.x] != '1')//reculer
// 		ctrl->p_player.y += 1, printf("down\n");
// 	else if (keysym == XK_d && ctrl->map->map[ctrl->p_player.y][ctrl->p_player.x+1] != '1')//aller a droite
// 		ctrl->p_player.x += 1, printf("right\n");
// 	else
// 		mv = false;
// 	return (mv);
// }

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
