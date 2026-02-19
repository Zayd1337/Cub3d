#include "../../includes/cube3d.h"

int	end(t_ctrl *ctrl)
{
	// free_struct_img(ctrl);
	mlx_destroy_window(ctrl->mlx, ctrl->win);
	mlx_destroy_display(ctrl->mlx);
	free(ctrl->mlx);
	// free_struct_ctrl(ctrl);
	exit(0);
}
