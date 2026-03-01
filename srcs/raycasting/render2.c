#include "../../includes/cube3d.h"

// pts[i] = {avance, lateral} depuis le centre du joueur
static void	draw_arrow_pts(t_ctrl *ctrl, t_data *img, t_xy c, t_coor perp)
{
	static const double	pts[7][2] = {
		{ 3,  0},  // pointe
		{ 1, -2},  // epaule gauche
		{ 1,  2},  // epaule droite
		{ 0,  0},  // centre
		{-1,  0},  // queue 1
		{ 0, -1},  // queue gauche
		{ 0,  1},  // queue droite
	};
	t_xy	p;
	int		i;

	i = 0;
	while (i < 7)
	{
		p.x = c.x + (int)round(ctrl->player.dir.x * pts[i][0] + perp.x * pts[i][1]);
		p.y = c.y + (int)round(ctrl->player.dir.y * pts[i][0] + perp.y * pts[i][1]);
		my_mlx_pixel_put(img, p, ctrl->img.to_print.img_dim, 0xE32925);
		i++;
	}
}

// Fleche dynamique basee sur player.dir (suit la rotation en temps reel)
int	add_player(t_ctrl *ctrl, t_data *img)
{
	t_coor	perp;
	t_xy	c;

	if (!img)
		return (MALLOC);
	perp.x = -ctrl->player.dir.y;
	perp.y =  ctrl->player.dir.x;
	c.x = ctrl->p_minimap.x + (int)ctrl->player.precis.x;
	c.y = ctrl->p_minimap.y + (int)ctrl->player.precis.y;
	draw_arrow_pts(ctrl, img, c, perp);
	return (SUCCES);
}

// copie F_C (fond), overlay minimap, affiche le joueur
int	render(t_ctrl *ctrl)
{
	int		y;
	int		m_y;
	char	*dst;
	char	*src;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		ft_memcpy(ctrl->img.to_print.addr + (y * ctrl->img.to_print.x_len),
			ctrl->img.F_C.addr + (y * ctrl->img.F_C.x_len),
			ctrl->img.F_C.x_len);
		if (y >= ctrl->p_minimap.y && y < ctrl->p_minimap.y + ctrl->img.minimap.img_dim.y)
		{
			m_y = y - ctrl->p_minimap.y;
			dst = ctrl->img.to_print.addr + (y * ctrl->img.to_print.x_len) + (ctrl->p_minimap.x * 4);
			src = ctrl->img.minimap.addr + (m_y * ctrl->img.minimap.x_len);
			ft_memcpy(dst, src, ctrl->img.minimap.x_len);
		}
		y++;
	}
	add_player(ctrl, &ctrl->img.to_print);
	mlx_put_image_to_window(ctrl->mlx, ctrl->win, ctrl->img.to_print.img, 0, 0);
	return (SUCCES);
}
