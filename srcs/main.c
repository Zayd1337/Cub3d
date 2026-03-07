#include "../includes/cube3d.h"

int	main(int argc, char **argv)
{
	t_ctrl	ctrl;

	init_struct(&ctrl);
	if (parse_data(&ctrl, argc, argv) != SUCCES)
		return (print_error(&ctrl), free_all(&ctrl), 1);
	if (init_minilibx(&ctrl) != SUCCES)
		return (print_error(&ctrl), free_all(&ctrl), 1);
	if (prepare_static(&ctrl) != SUCCES)
		return (print_error(&ctrl), free_all(&ctrl), 1);

	if (render(&ctrl) != SUCCES)
		return (print_error(&ctrl), free_all(&ctrl), 1);
	mlx_hook(ctrl.win, DestroyNotify, 0, &end, &ctrl);
	mlx_hook(ctrl.win, KeyPress, KeyPressMask, &keypress, &ctrl);
	mlx_hook(ctrl.win, KeyRelease, KeyReleaseMask, &keyrelease, &ctrl);
	mlx_loop_hook(ctrl.mlx, &move, &ctrl);
	mlx_loop(ctrl.mlx);
	return (free_all(&ctrl), 0);
}
