/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:45 by myokono           #+#    #+#             */
/*   Updated: 2024/09/20 19:07:13 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

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

int	ft_close_win(void *prm)
{
	t_fdf	*fdf;

	fdf = prm;
	ft_free_fdf(fdf);
	exit (0);
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

static int	ft_key_press(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
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
	return (0);
}

static int	ft_close_esc(int keycode, t_fdf *fdf)
{
	if (!(keycode == 53))
		return (0);
	ft_free_fdf(fdf);
	exit (0);
}

void	ft_setup_controls(t_fdf *fdf)
{
	mlx_key_hook(fdf->window, ft_close_esc, fdf);
	mlx_hook(fdf->window, 17, 0, ft_close_win, fdf);
	mlx_key_hook(fdf->window, ft_key_press, fdf);
	mlx_hook(fdf->window, 4, 0, ft_mouse_press, fdf);
	mlx_hook(fdf->window, 5, 0, ft_mouse_release, fdf);
	mlx_hook(fdf->window, 6, 0, ft_mouse_move, fdf);
}
