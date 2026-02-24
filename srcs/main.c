#include "../includes/cube3d.h"

int	main(int argc, char **argv)
{
	t_ctrl	ctrl;

	init_struct(&ctrl);
	if (parse_data(&ctrl, argc, argv) == false)
		return (free_all(&ctrl), 1);
	if (init_minilibx(&ctrl) == false)
		return (free_all(&ctrl), 1);
	// if (raycasting() == false)
	// 	return (false);
	mlx_hook(ctrl.win, KeyPress, KeyPressMask, &keypress, &ctrl);//attends les input clavier, ESC
	mlx_hook(ctrl.win, DestroyNotify, 0, &end, &ctrl);//gestion croix fenetre
	mlx_loop(ctrl.mlx);
	return (free_all(&ctrl), 0);//jamais atteint normalement
}
