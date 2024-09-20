/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:45 by myokono           #+#    #+#             */
/*   Updated: 2024/09/20 17:10:43 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

// int	ft_hook_mousedown(int button, int x, int y, t_fdf *fdf)
// {
// 	(void)x;
// 	if (y < 0)
// 		return (0);
// 	fdf->mouse->isdown |= 1 << button;
// 	return (0);
// }

// int	ft_hook_mouseup(int button, int x, int y, t_fdf *fdf)
// {
// 	(void)x;
// 	(void)y;
// 	fdf->mouse->isdown &= ~(1 << button);
// 	return (0);
// }

// int	ft_hook_mousemove(int x, int y, t_fdf *fdf)
// {
// 	if (fdf->cam->projection == ISO)
// 		fdf->cam->projection = PARALLEL;
// 	fdf->mouse->lastx = fdf->mouse->x;
// 	fdf->mouse->lasty = fdf->mouse->y;
// 	fdf->mouse->x = x;
// 	fdf->mouse->y = y;
// 	if (fdf->mouse->isdown & (1 << 1) && fdf->mouse->isdown & (1 << 2))
// 	{
// 		fdf->cam->offsetx += (x - fdf->mouse->lastx);
// 		fdf->cam->offsety += (y - fdf->mouse->lasty);
// 	}
// 	else if (fdf->mouse->isdown & (1 << 1))
// 	{
// 		fdf->cam->x += (fdf->mouse->lasty - y) / 200.0f;
// 		fdf->cam->y -= (fdf->mouse->lastx - x) / 200.0f;
// 	}
// 	else if (fdf->mouse->isdown & (1 << 2))
// 	{
// 		fdf->cam->scale += (fdf->mouse->lasty - y) / 10.0f + 0.5f;
// 		if (fdf->cam->scale < 1)
// 			fdf->cam->scale = 1;
// 	}
// 	if (fdf->mouse->isdown)
// 		ft_render(fdf);
// 	return (0);
// }

// int	ft_hook_keydown(int key, t_fdf *fdf)
// {
// 	(void)fdf;
// 	if (key == 53)
// 		exit(EXIT_SUCCESS);
// 	return (0);
// }

void	ft_zoom(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_PLUS || key == MAIN_PAD_PLUS || \
		key == MOUSE_SCROLL_UP)
		fdf->cam->zoom++;
	else if (key == NUM_PAD_MINUS || key == MAIN_PAD_MINUS || \
		key == MOUSE_SCROLL_DOWN)
		fdf->cam->zoom--;
	if (fdf->cam->zoom < 1)
		fdf->cam->zoom = 1;
	ft_render(fdf);
}

void	ft_move(int key, t_fdf *fdf)
{
	if (key == ARROW_LEFT)
		fdf->cam->offsetx -= 10;
	else if (key == ARROW_RIGHT)
		fdf->cam->offsetx += 10;
	else if (key == ARROW_UP)
		fdf->cam->offsety -= 10;
	else
		fdf->cam->offsety += 10;
	ft_render(fdf);
}

int	ft_close(void *param)
{
	(void)param;
	exit(0);
}

void	ft_rotate(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_2 || key == MAIN_PAD_2)
		fdf->cam->alpha += 0.05;
	else if (key == NUM_PAD_8 || key == MAIN_PAD_8)
		fdf->cam->alpha -= 0.05;
	else if (key == NUM_PAD_4 || key == MAIN_PAD_4)
		fdf->cam->beta -= 0.05;
	else if (key == NUM_PAD_6 || key == MAIN_PAD_6)
		fdf->cam->beta += 0.05;
	else if (key == NUM_PAD_1 || key == MAIN_PAD_1
		|| key == NUM_PAD_3 || key == MAIN_PAD_3)
		fdf->cam->gamma += 0.05;
	else if (key == NUM_PAD_7 || key == MAIN_PAD_7
		|| key == NUM_PAD_9 || key == MAIN_PAD_9)
		fdf->cam->gamma -= 0.05;
	ft_render(fdf);
}

void	ft_flatten(int key, t_fdf *fdf)
{
	if (key == MAIN_PAD_LESS)
		fdf->cam->z_divisor -= 0.1;
	else if (key == MAIN_PAD_MORE)
		fdf->cam->z_divisor += 0.1;
	if (fdf->cam->z_divisor < 0.1)
		fdf->cam->z_divisor = 0.1;
	else if (fdf->cam->z_divisor > 10)
		fdf->cam->z_divisor = 10;
	ft_render(fdf);
}

// static void	ft_change_projection(int key, t_fdf *fdf)
// {
// 	fdf->cam->alpha = 0;
// 	fdf->cam->beta = 0;
// 	fdf->cam->gamma = 0;
// 	if (key == MAIN_PAD_I)
// 		fdf->cam->projection = ISO;
// 	else if (key == MAIN_PAD_P)
// 		fdf->cam->projection = PARALLEL;
// 	ft_render(fdf);
// }


static int	ft_key_press(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == NUM_PAD_PLUS || key == MAIN_PAD_PLUS
		|| key == NUM_PAD_MINUS || key == MAIN_PAD_MINUS)
		ft_zoom(key, fdf);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT
		|| key == ARROW_UP || key == ARROW_DOWN)
		ft_move(key, fdf);
	else if (key == NUM_PAD_1 || key == MAIN_PAD_1
		|| key == NUM_PAD_2 || key == MAIN_PAD_2
		|| key == NUM_PAD_3 || key == MAIN_PAD_3
		|| key == NUM_PAD_4 || key == MAIN_PAD_4
		|| key == NUM_PAD_6 || key == MAIN_PAD_6
		|| key == NUM_PAD_7 || key == MAIN_PAD_7
		|| key == NUM_PAD_8 || key == MAIN_PAD_8
		|| key == NUM_PAD_9 || key == MAIN_PAD_9)
		ft_rotate(key, fdf);
	else if (key == MAIN_PAD_LESS || key == MAIN_PAD_MORE)
		ft_flatten(key, fdf);
	// else if (key == MAIN_PAD_P || key == MAIN_PAD_I)
	// 	ft_change_projection(key, fdf);
	return (0);
}

void	ft_setup_controls(t_fdf *fdf)
{
	mlx_key_hook(fdf->window, ft_key_press, fdf);
	mlx_hook(fdf->window, 17, 0, ft_close, fdf);
	mlx_hook(fdf->window, 4, 0, ft_mouse_press, fdf);
	mlx_hook(fdf->window, 5, 0, ft_mouse_release, fdf);
	mlx_hook(fdf->window, 6, 0, ft_mouse_move, fdf);
}
