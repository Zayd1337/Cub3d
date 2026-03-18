/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:08:06 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 14:08:08 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

bool	check_collision(t_ctrl *ctrl, double next_x, double next_y)
{
	t_xy	xy;

	if (!ctrl->map || !ctrl->map->map)
		return (printf("map doesn't exist\n"), false);
	xy.x = (int)(next_x / ctrl->tile_size);
	xy.y = (int)(next_y / ctrl->tile_size);
	if (xy.y < 0 || xy.y >= (int)ctrl->map->nb_line || xy.x < 0
		|| xy.x >= (int)ctrl->map->len_line)
		return (false);
	if (ctrl->map->map[xy.y][xy.x] == '1')
		return (false);
	return (true);
}

static void	set_next_step(t_ctrl *ctrl, t_coor *move)
{
	double	speed;

	speed = ctrl->move_speed;
	if (ctrl->key_press[0])
	{
		move->x += ctrl->player.dir.x * speed;
		move->y += ctrl->player.dir.y * speed;
	}
	if (ctrl->key_press[1])
	{
		move->x -= ctrl->player.dir.x * speed;
		move->y -= ctrl->player.dir.y * speed;
	}
	if (ctrl->key_press[2])
	{
		move->x += ctrl->player.dir.y * speed;
		move->y -= ctrl->player.dir.x * speed;
	}
	if (ctrl->key_press[3])
	{
		move->x -= ctrl->player.dir.y * speed;
		move->y += ctrl->player.dir.x * speed;
	}
}

bool	walk(t_ctrl *ctrl)
{
	t_coor	move;
	double	margin;

	move.x = 0;
	move.y = 0;
	set_next_step(ctrl, &move);
	if (move.x == 0 && move.y == 0)
		return (false);
	if (move.x > 0)
		margin = 2;
	else
		margin = -2;
	if (check_collision(ctrl, ctrl->player.precis.x + move.x + margin,
			ctrl->player.precis.y))
		ctrl->player.precis.x += move.x;
	if (move.y > 0)
		margin = 2;
	else
		margin = -2;
	if (check_collision(ctrl, ctrl->player.precis.x, ctrl->player.precis.y
			+ move.y + margin))
		ctrl->player.precis.y += move.y;
	return (true);
}

bool	rotate(t_ctrl *ctrl)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	if (!ctrl->key_press[4] && !ctrl->key_press[5])
		return (false);
	if (ctrl->key_press[4])
		angle = -ctrl->rot_speed;
	else
		angle = ctrl->rot_speed;
	old_dir_x = ctrl->player.dir.x;
	ctrl->player.dir.x = ctrl->player.dir.x * cos(angle) - ctrl->player.dir.y
		* sin(angle);
	ctrl->player.dir.y = old_dir_x * sin(angle) + ctrl->player.dir.y
		* cos(angle);
	old_plane_x = ctrl->player.plane.x;
	ctrl->player.plane.x = ctrl->player.plane.x * cos(angle)
		- ctrl->player.plane.y * sin(angle);
	ctrl->player.plane.y = old_plane_x * sin(angle) + ctrl->player.plane.y
		* cos(angle);
	return (true);
}

int	move(t_ctrl *ctrl)
{
	struct timeval	tv;
	long			time;
	double			frame_time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	frame_time = (time - ctrl->old_time) / 1000.0;
	ctrl->old_time = time;
	ctrl->move_speed = frame_time * MOVE_SPEED * ctrl->tile_size;
	ctrl->rot_speed = frame_time * ROT_SPEED;
	if (walk(ctrl) | rotate(ctrl))
		render(ctrl);
	return (0);
}
