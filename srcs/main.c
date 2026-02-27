#include "../includes/cube3d.h"

// void	fill_square(t_data *img, int color, int size, t_xy start)
// {
// 	t_xy	pixel;

// 	if (color == -1)
// 		return ;
// 	static int z = 1;
// 	printf ("red point %d: (%d, %d)\n", z, start.y*size, start.x*size);
// 	z++;
// 	pixel.y = start.y*size;
// 	while (pixel.y < size)
// 	{
// 		pixel.x = start.x*size;
// 		printf ("pixel.x = %d vs %d\n", pixel.x, size);
// 		while (pixel.x < size)
// 		{
// 			printf ("dans x\n");
// 			if (pixel.x < 4 && pixel.y < 4)
// 				my_mlx_pixel_put(img, pixel, 0xFF0000);
// 			else
// 				my_mlx_pixel_put(img, pixel, color);
// 			pixel.x++;
// 		}
// 		pixel.y++;
// 	}
// }


// int	print_player(t_ctrl *ctrl)
// {
// 	my_mlx_pixel_put(ctrl->img.player)
// }



int	main(int argc, char **argv)
{
	t_ctrl	ctrl;

	init_struct(&ctrl);
	if (parse_data(&ctrl, argc, argv) != SUCCES)
		return (print_error(&ctrl), free_all(&ctrl), 1);
	// printf ("error : %d\n", ctrl.error);
	// // print_error(&ctrl);
	// // print_map_infos(&ctrl);
	if (init_minilibx(&ctrl) != SUCCES)
		return (print_error(&ctrl), free_all(&ctrl), 1);
	if (prepare_static(&ctrl) != SUCCES)
		return (print_error(&ctrl), free_all(&ctrl), 1);
	// if (raycasting() == false)
	// 	return (false);
	if (render(&ctrl) != SUCCES)
		return (print_error(&ctrl), free_all(&ctrl), 1);
	mlx_hook(ctrl.win, DestroyNotify, 0, &end, &ctrl);
	mlx_hook(ctrl.win, KeyPress, KeyPressMask, &keypress, &ctrl);
	mlx_hook(ctrl.win, KeyRelease, KeyReleaseMask, &keyrelease, &ctrl);
	mlx_loop_hook(ctrl.mlx, &move, &ctrl);
	mlx_loop(ctrl.mlx);
	return (free_all(&ctrl), 0);
}
