#include "../includes/cube3d.h"

int	main(int argc, char **argv)
{
	t_ctrl	ctrl;

	init_struct(&ctrl);
	if (parse_data(&ctrl, argc, argv) != SUCCES)
		return (free_all(&ctrl), print_error(&ctrl), 1);
	// printf ("error : %d\n", ctrl.error);
	// // print_error(&ctrl);
	// // print_map_infos(&ctrl);
	if (init_minilibx(&ctrl) == false)
		return (free_all(&ctrl), 1);
	// if (raycasting() == false)
	// 	return (false);
	mlx_hook(ctrl.win, KeyPress, KeyPressMask, &keypress, &ctrl);
	mlx_hook(ctrl.win, DestroyNotify, 0, &end, &ctrl);
	mlx_loop(ctrl.mlx);
	return (free_all(&ctrl), 0);
}
