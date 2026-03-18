/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:39:48 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/18 09:39:48 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	draw_arrow_pts(t_ctrl *ctrl, t_data *img, t_xy c, t_coor perp)
{
	t_xy				p;
	int					i;
	static const double	pts[7][2] = {{3, 0}, {1, -2}, {1, 2}, \
		{0, 0}, {-1, 0}, {0, -1}, {0, 1}};

	i = 0;
	while (i < 7)
	{
		p.x = c.x + (int)round(ctrl->player.dir.x * pts[i][0] + perp.x
				* pts[i][1]);
		p.y = c.y + (int)round(ctrl->player.dir.y * pts[i][0] + perp.y
				* pts[i][1]);
		my_mlx_pixel_put(img, p, ctrl->img.to_print.img_dim, 0xE32925);
		i++;
	}
}

int	add_player(t_ctrl *ctrl, t_data *img)
{
	t_coor	perp;
	t_xy	c;

	if (!img)
		return (MALLOC);
	perp.x = -ctrl->player.dir.y;
	perp.y = ctrl->player.dir.x;
	c.x = ctrl->p_minimap.x + (int)ctrl->player.precis.x;
	c.y = ctrl->p_minimap.y + (int)ctrl->player.precis.y;
	draw_arrow_pts(ctrl, img, c, perp);
	return (SUCCES);
}

static void	overlay_minimap(t_ctrl *ctrl)
{
	int		y;
	int		m_y;
	char	*dst;
	char	*src;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y >= ctrl->p_minimap.y && y < ctrl->p_minimap.y
			+ ctrl->img.minimap.img_dim.y)
		{
			m_y = y - ctrl->p_minimap.y;
			dst = ctrl->img.to_print.addr + (y * ctrl->img.to_print.x_len)
				+ (ctrl->p_minimap.x * 4);
			src = ctrl->img.minimap.addr + (m_y * ctrl->img.minimap.x_len);
			ft_memcpy(dst, src, ctrl->img.minimap.x_len);
		}
		y++;
	}
}

int	render(t_ctrl *ctrl)
{
	if (render_frame(ctrl) != SUCCES)
		return (MALLOC);
	overlay_minimap(ctrl);
	add_player(ctrl, &ctrl->img.to_print);
	mlx_put_image_to_window(ctrl->mlx, ctrl->win, ctrl->img.to_print.img, 0,
		0);
	return (SUCCES);
}
