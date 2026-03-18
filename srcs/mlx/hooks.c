/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:08:03 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 14:08:34 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	end(t_ctrl *ctrl)
{
	free_all(ctrl);
	exit(0);
	return (0);
}

int	keypress(int keysym, t_ctrl *ctrl)
{
	if (keysym == XK_Escape)
		end(ctrl);
	if (keysym == XK_w)
		ctrl->key_press[0] = true;
	if (keysym == XK_s)
		ctrl->key_press[1] = true;
	if (keysym == XK_a)
		ctrl->key_press[2] = true;
	if (keysym == XK_d)
		ctrl->key_press[3] = true;
	if (keysym == XK_Left)
		ctrl->key_press[4] = true;
	if (keysym == XK_Right)
		ctrl->key_press[5] = true;
	return (0);
}

int	keyrelease(int keysym, t_ctrl *ctrl)
{
	if (keysym == XK_w)
		ctrl->key_press[0] = false;
	if (keysym == XK_s)
		ctrl->key_press[1] = false;
	if (keysym == XK_a)
		ctrl->key_press[2] = false;
	if (keysym == XK_d)
		ctrl->key_press[3] = false;
	if (keysym == XK_Left)
		ctrl->key_press[4] = false;
	if (keysym == XK_Right)
		ctrl->key_press[5] = false;
	return (0);
}
