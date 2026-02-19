#include "../includes/cube3d.h"

int	main(int argc, char **argv)
{
	t_ctrl	ctrl;
	// char	**map;

	init_struct(&ctrl);
	if (set_data(&ctrl, argc, argv) == false)
		return (1);//printf("Error\nInvalid input\n"), 
	// // mlx_hook(ctrl.win, KeyPress, KeyPressMask, &keypress, &ctrl);//attends les input clavier
	// mlx_hook(ctrl.win, 17, 0, &end, &ctrl);
	// mlx_loop(ctrl.mlx);
	free_all(&ctrl);
	return (0);
}