/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:45 by myokono           #+#    #+#             */
/*   Updated: 2024/09/19 00:36:06 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	ft_close_win(void *prm)
{
	t_fdf	*fdf;

	fdf = prm;
	ft_free_fdf(fdf);
	exit (0);
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
}
