/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:07:48 by myokono           #+#    #+#             */
/*   Updated: 2024/09/20 16:49:08 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

int	ft_mouse_press(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		ft_zoom(button, fdf);
	else if (button == MOUSE_LEFT_BUTTON)
		fdf->mouse->isdown = true;
	return (0);
}

int	ft_mouse_release(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	(void)x;
	(void)y;
	(void)button;
	fdf = (t_fdf *)param;
	fdf->mouse->isdown = false;
	return (0);
}

int	ft_mouse_move(int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	fdf->mouse->lastx = fdf->mouse->x;
	fdf->mouse->lasty = fdf->mouse->y;
	fdf->mouse->x = x;
	fdf->mouse->y = y;
	if (fdf->mouse->isdown)
	{
		fdf->cam->beta += (x - fdf->mouse->lastx) * 0.002;
		fdf->cam->alpha += (y - fdf->mouse->lasty) * 0.002;
		ft_render(fdf);
	}
	return (0);
}
