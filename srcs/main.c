#include "../includes/cube3d.h"

int	main(int argc, char **argv)
{
	t_ctrl	ctrl;
	// char	**map;

	init_struct(&ctrl);
	if (check_input(&ctrl, argc, argv) == false)
		return (1);//printf("Error\nInvalid input\n"), 
	// map = get_map(argv[1]);
	// if (map == NULL)
	// 	return (printf("Error\nIncorrect or non-existent map\n"), 1);
	
	// // mlx_hook(ctrl.win, KeyPress, KeyPressMask, &keypress, &ctrl);//attends les input clavier
	// mlx_hook(ctrl.win, 17, 0, &end, &ctrl);
	// mlx_loop(ctrl.mlx);
	free_all(&ctrl);
	return (0);
}