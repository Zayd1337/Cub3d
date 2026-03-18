/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:34:15 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 17:34:16 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	init_map(t_ctrl *ctrl, char *name)
{
	ctrl->map = malloc(sizeof(t_map));
	if (!ctrl->map)
		return ((ctrl->error = MALLOC), ctrl->error);
	if (name)
	{
		ctrl->map->name = ft_strdup(name);
		if (!ctrl->map->name)
			return ((ctrl->error = MALLOC), ctrl->error);
	}
	ctrl->map->temp_map = NULL;
	ctrl->map->map_stock = NULL;
	ctrl->map->map = NULL;
	ctrl->map->nb_line = 0;
	ctrl->map->len_line = 0;
	ctrl->map->colors_set = 0;
	ctrl->map->textures_set = 0;
	ctrl->map->map_set = false;
	ctrl->map->orientation = -1;
	init_textures_colors(ctrl->map);
	return (SUCCES);
}

void	init_struct(t_ctrl *ctrl)
{
	int				i;
	struct timeval	tv;

	ctrl->error = SUCCES;
	ctrl->map = NULL;
	ctrl->win = NULL;
	ctrl->mlx = NULL;
	i = 0;
	while (i < 6)
		ctrl->key_press[i++] = false;
	ctrl->img.no.img = NULL;
	ctrl->img.so.img = NULL;
	ctrl->img.ea.img = NULL;
	ctrl->img.we.img = NULL;
	ctrl->img.f_c.img = NULL;
	ctrl->img.minimap.img = NULL;
	ctrl->img.to_print.img = NULL;
	gettimeofday(&tv, NULL);
	ctrl->old_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	ctrl->move_speed = 0;
	ctrl->rot_speed = 0;
}

void	init_textures_colors(t_map *map)
{
	map->color[0] = -1;
	map->color[1] = -1;
	map->textures[0] = NULL;
	map->textures[1] = NULL;
	map->textures[2] = NULL;
	map->textures[3] = NULL;
}
