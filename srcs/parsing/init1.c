/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:34:09 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 17:34:12 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static bool	set_tile_size(t_ctrl *ctrl)
{
	t_xy	screen_size;

	if (ctrl->map->len_line == 0 || ctrl->map->nb_line == 0)
		return (false);
	screen_size.x = WIN_WIDTH / 4 / ctrl->map->len_line;
	screen_size.y = WIN_HEIGHT / 4 / ctrl->map->nb_line;
	ctrl->tile_size = screen_size.x;
	if (screen_size.y < screen_size.x)
		ctrl->tile_size = screen_size.y;
	return (true);
}

static void	set_ew_orientation(t_ctrl *ctrl)
{
	if (ctrl->map->orientation == 2)
	{
		ctrl->player.dir.x = 1;
		ctrl->player.dir.y = 0;
		ctrl->player.plane.x = 0;
		ctrl->player.plane.y = 0.66;
	}
	if (ctrl->map->orientation == 3)
	{
		ctrl->player.dir.x = -1;
		ctrl->player.dir.y = 0;
		ctrl->player.plane.x = 0;
		ctrl->player.plane.y = -0.66;
	}
}

static void	set_ns_orientation(t_ctrl *ctrl)
{
	if (ctrl->map->orientation == 0)
	{
		ctrl->player.dir.x = 0;
		ctrl->player.dir.y = -1;
		ctrl->player.plane.x = 0.66;
		ctrl->player.plane.y = 0;
	}
	else if (ctrl->map->orientation == 1)
	{
		ctrl->player.dir.x = 0;
		ctrl->player.dir.y = 1;
		ctrl->player.plane.x = -0.66;
		ctrl->player.plane.y = 0;
	}
}

int	init_minilibx(t_ctrl *ctrl)
{
	ctrl->mlx = mlx_init();
	if (!ctrl->mlx)
		return ((ctrl->error = MALLOC), ctrl->error);
	set_tile_size(ctrl);
	ctrl->player.precis.x = ctrl->player.map_c.x * ctrl->tile_size
		+ ctrl->tile_size / 2;
	ctrl->player.precis.y = ctrl->player.map_c.y * ctrl->tile_size
		+ ctrl->tile_size / 2;
	set_ns_orientation(ctrl);
	set_ew_orientation(ctrl);
	ctrl->win = mlx_new_window(ctrl->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!ctrl->win)
		return ((ctrl->error = MALLOC), ctrl->error);
	if (set_img(ctrl) == false)
		return ((ctrl->error = MALLOC), ctrl->error);
	ctrl->p_minimap.x = WIN_WIDTH - 20 - ctrl->img.minimap.img_dim.x;
	ctrl->p_minimap.y = 20;
	return (SUCCES);
}
