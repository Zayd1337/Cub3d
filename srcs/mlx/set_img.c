/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:08:09 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 14:19:03 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static bool	set_to_print_window(t_ctrl *ctrl)
{
	ctrl->img.to_print.img_dim.x = WIN_WIDTH;
	ctrl->img.to_print.img_dim.y = WIN_HEIGHT;
	ctrl->img.to_print.img = mlx_new_image(ctrl->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (ctrl->img.to_print.img == NULL)
		return (false);
	ctrl->img.to_print.addr = mlx_get_data_addr(ctrl->img.to_print.img,
			&ctrl->img.to_print.bpp, &ctrl->img.to_print.x_len,
			&ctrl->img.to_print.endian);
	if (ctrl->img.to_print.addr == NULL)
		return (false);
	return (true);
}

static bool	set_win_elem(t_ctrl *ctrl)
{
	ctrl->img.f_c.img_dim.x = WIN_WIDTH;
	ctrl->img.f_c.img_dim.y = WIN_HEIGHT;
	ctrl->img.f_c.img = mlx_new_image(ctrl->mlx, ctrl->img.f_c.img_dim.x,
			ctrl->img.f_c.img_dim.y);
	if (ctrl->img.f_c.img == NULL)
		return (false);
	ctrl->img.f_c.addr = mlx_get_data_addr(ctrl->img.f_c.img,
			&ctrl->img.f_c.bpp, &ctrl->img.f_c.x_len, &ctrl->img.f_c.endian);
	if (ctrl->img.f_c.addr == NULL)
		return (false);
	ctrl->img.minimap.img_dim.x = ctrl->map->len_line * ctrl->tile_size;
	ctrl->img.minimap.img_dim.y = ctrl->map->nb_line * ctrl->tile_size;
	ctrl->img.minimap.img = mlx_new_image(ctrl->mlx,
			ctrl->img.minimap.img_dim.x, ctrl->img.minimap.img_dim.y);
	if (ctrl->img.minimap.img == NULL)
		return (false);
	ctrl->img.minimap.addr = mlx_get_data_addr(ctrl->img.minimap.img,
			&ctrl->img.minimap.bpp, &ctrl->img.minimap.x_len,
			&ctrl->img.minimap.endian);
	if (ctrl->img.minimap.addr == NULL)
		return (false);
	return (true);
}

static bool	set_ea_we(t_ctrl *ctrl)
{
	ctrl->img.ea.img = mlx_xpm_file_to_image(ctrl->mlx, ctrl->map->textures[2],
			&ctrl->img.ea.img_dim.x, &ctrl->img.ea.img_dim.y);
	if (ctrl->img.ea.img == NULL)
		return (false);
	ctrl->img.ea.addr = mlx_get_data_addr(ctrl->img.ea.img, &ctrl->img.ea.bpp,
			&ctrl->img.ea.x_len, &ctrl->img.ea.endian);
	if (ctrl->img.ea.addr == NULL)
		return (false);
	ctrl->img.we.img = mlx_xpm_file_to_image(ctrl->mlx, ctrl->map->textures[3],
			&ctrl->img.we.img_dim.x, &ctrl->img.we.img_dim.y);
	if (ctrl->img.we.img == NULL)
		return (false);
	ctrl->img.we.addr = mlx_get_data_addr(ctrl->img.we.img, &ctrl->img.we.bpp,
			&ctrl->img.we.x_len, &ctrl->img.we.endian);
	if (ctrl->img.we.addr == NULL)
		return (false);
	return (true);
}

static bool	set_no_so(t_ctrl *ctrl)
{
	ctrl->img.no.img = mlx_xpm_file_to_image(ctrl->mlx, ctrl->map->textures[0],
			&ctrl->img.no.img_dim.x, &ctrl->img.no.img_dim.y);
	if (ctrl->img.no.img == NULL)
		return (false);
	ctrl->img.no.addr = mlx_get_data_addr(ctrl->img.no.img, &ctrl->img.no.bpp,
			&ctrl->img.no.x_len, &ctrl->img.no.endian);
	if (ctrl->img.no.addr == NULL)
		return (false);
	ctrl->img.so.img = mlx_xpm_file_to_image(ctrl->mlx, ctrl->map->textures[1],
			&ctrl->img.so.img_dim.x, &ctrl->img.so.img_dim.y);
	if (ctrl->img.so.img == NULL)
		return (false);
	ctrl->img.so.addr = mlx_get_data_addr(ctrl->img.so.img, &ctrl->img.so.bpp,
			&ctrl->img.so.x_len, &ctrl->img.so.endian);
	if (ctrl->img.so.addr == NULL)
		return (false);
	return (true);
}

bool	set_img(t_ctrl *ctrl)
{
	if (set_no_so(ctrl) == false)
		return (false);
	if (set_ea_we(ctrl) == false)
		return (false);
	if (set_win_elem(ctrl) == false)
		return (false);
	if (set_to_print_window(ctrl) == false)
		return (false);
	return (true);
}
