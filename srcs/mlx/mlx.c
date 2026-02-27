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

// void	set_next(t_ctrl *ctrl, t_coor *next, bool key_press[6], double step)
// {
// 	int key;

// 	key = 0;
// 	while (key_press[key] != true)
// 		key++;
// 	next->x = ctrl->player.precis.x;
//     next->y = ctrl->player.precis.y;

//     if (key == 0)// avancer
//         next->y -= step;
//     else if (key == 1)// reculer
//         next->y += step;
//     else if (key == 2) // gauche
//         next->x -= step;
//     else if (key == 3)// Droite
//         next->x += step;
// }

bool	check_collision(t_ctrl *ctrl, double next_x, double next_y)
{
	t_xy xy;

	if (!ctrl->map || !ctrl->map->map)
		return (printf("map doesn't exist\n"), false);
	xy.x = (int)next_x/ctrl->tile_size;
	xy.y = (int)next_y/ctrl->tile_size;
	if (ctrl->map->map[xy.y][xy.x] == '1')
		return (printf("wall detected\n"), false);
	return (true);
}

int move(t_ctrl *ctrl)
{
    double move_x = 0;
    double move_y = 0;
	t_coor next;

    if (ctrl->key_press[0]) 
		move_y -= SPEED; // W
    if (ctrl->key_press[2]) 
		move_y += SPEED; // S
    if (ctrl->key_press[1]) 
		move_x -= SPEED; // A
    if (ctrl->key_press[3]) 
		move_x += SPEED; // D
    if (move_x == 0 && move_y == 0)
        return (0);
    
    next.x = ctrl->player.precis.x + move_x;
    next.y = ctrl->player.precis.y + move_y;
    if (check_collision(ctrl, next.x, next.y))
    {
        ctrl->player.precis = next;
		printf ("move\n");
        render(ctrl);
    }
    return (0);
}

// int	move(t_ctrl *ctrl)
// {
// 	t_coor next;
// 	t_xy tile;

// 	if (!ctrl->map || !ctrl->map->map)
// 		return (false);
// 	set_next(ctrl, &next, ctrl->key_press, SPEED);
// 	tile.x = (int)next.x/ctrl->tile_size;//ptetre pas ouf la division
// 	tile.y = (int)next.y/ctrl->tile_size;
// 	printf ("test map[%d][%d]\n", tile.y, tile.x);
//     if (ctrl->map->map[tile.y][tile.x] != '1')
//     {
//         ctrl->player.precis.x = next.x;
//         ctrl->player.precis.y = next.y;
// 		ctrl->player.map_c.x = tile.x;
//         ctrl->player.map_c.y = tile.y;
// 		if (render(ctrl) != SUCCES)
// 			return (false);
//         return (true);
//     }
//     return (printf("move impossible\n"), false);
// }

// int move(t_ctrl *ctrl)
// {
//     t_coor next;
//     t_xy tile;
//     int i = 0;

//     while (i < 4) // On check W, A, S, D
//     {
//         if (ctrl->key_press[i])
//         {
//             set_next(ctrl, &next, i, SPEED); // i est la direction
//             tile.x = (int)next.x / ctrl->tile_size;
//             tile.y = (int)next.y / ctrl->tile_size;

//             // SECURITE : Vérifier si on est dans les limites de la map
//             if (tile.y >= 0 && tile.y < (int)ctrl->map->nb_line && 
//                 tile.x >= 0 && tile.x < (int)ctrl->map->len_line)
//             {
//                 if (ctrl->map->map[tile.y][tile.x] != '1')
//                 {
//                     ctrl->player.precis.x = next.x;
//                     ctrl->player.precis.y = next.y;
//                 }
//             }
//         }
//         i++;
//     }
//     render(ctrl);
//     return (0);
// }

int keypress(int keysym, t_ctrl *ctrl)
{
    if (keysym == XK_Escape)
		end(ctrl);
    if (keysym == XK_w) 
		ctrl->key_press[0] = true;
    if (keysym == XK_a) 
		ctrl->key_press[1] = true;
    if (keysym == XK_s) 
		ctrl->key_press[2] = true;
    if (keysym == XK_d) 
		ctrl->key_press[3] = true;
    return (0);
}

//???
int keyrelease(int keysym, t_ctrl *ctrl)
{
    if (keysym == XK_w) 
		ctrl->key_press[0] = false;
    if (keysym == XK_a) 
		ctrl->key_press[1] = false;
    if (keysym == XK_s) 
		ctrl->key_press[2] = false;
    if (keysym == XK_d) 
		ctrl->key_press[3] = false;
    return (0);
}

// int player_mov(t_ctrl *ctrl, int keysym)
// {
//     double step = 1;
// 	t_coor next;
// 	t_xy tile;

//     // next.x = ctrl->player.precis.x;
//     // next.y = ctrl->player.precis.y;

//     // if (keysym == XK_w)// avancer
//     //     next.y -= step;
//     // else if (keysym == XK_s)// reculer
//     //     next.y += step;
//     // else if (keysym == XK_a) // gauche
//     //     next.x -= step;
//     // else if (keysym == XK_d)// Droite
//     //     next.x += step;
//     else
// 		return (false);
// 	tile.x = (int)next.x/ctrl->tile_size;
// 	tile.y = (int)next.y/ctrl->tile_size;
// 	printf ("test map[%d][%d]\n", tile.y, tile.x);
//     if (ctrl->map->map[tile.y][tile.x] != '1')
//     {
//         ctrl->player.precis.x = next.x;
//         ctrl->player.precis.y = next.y;
// 		ctrl->player.map_c.x = tile.x;
//         ctrl->player.map_c.y = tile.y;
// 		if (render(ctrl) != SUCCES)
// 			return (false);
//         return (true);
//     }
//     return (printf("move impossible\n"), false);
// }

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


// int	keyrelease(int keysym, t_ctrl *ctrl)
// {
// 	if (ctrl->key_press[0] == true && keysym != XK_w)
// 	{
// 		ctrl->moving = -1;
// 		ctrl->key_press[0] = false;
// 	}
// 	else if (ctrl->key_press[1] == true && keysym != XK_a)
// 	{
// 		ctrl->moving = -1;
// 		ctrl->key_press[1] = false;
// 	}
// 	else if (ctrl->key_press[2] == true && keysym != XK_s)
// 	{
// 		ctrl->moving = -1;
// 		ctrl->key_press[2] = false;
// 	}	
// 	else if (ctrl->key_press[3] == true && keysym != XK_d)
// 	{
// 		ctrl->moving = -1;
// 		ctrl->key_press[3] = false;
// 	}
// 	// else if (ctrl->key_press[4] == true && keysym != XK_Right)
// 	// 	ctrl->key_press[4] = false;
// 	// else if (ctrl->key_press[5] == true && keysym != XK_Left)
// 	// 	ctrl->key_press[5] = false;
// 	return (0);
// }

// int	keypress(int keysym, t_ctrl *ctrl)
// {
// 	if (keysym == XK_Escape)
// 		end(ctrl);
// 	// else if (keysym == XK_Right)
// 	// 	cam_mov();
// 	// else if (keysym == XK_Left)
// 	// 	cam_mov();
// 	else if (keysym == XK_w)//avancer
// 	{
// 		ctrl->key_press[0] = true;
// 		ctrl->moving = 0;
// 	}
// 	else if (keysym == XK_a)//aller a gauche
// 	{
// 		ctrl->key_press[1] = true;
// 		ctrl->moving = 1;
// 	}
// 	else if (keysym == XK_s)//reculer
// 	{
// 		ctrl->key_press[2] = true;
// 		ctrl->moving = 2;
// 	}
// 	else if (keysym == XK_d)//aller a droite
// 	{
// 		ctrl->key_press[3] = true;
// 		ctrl->moving = 3;
// 	}
// 	return (0);
// }
