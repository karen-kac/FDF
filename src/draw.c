/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:10 by myokono           #+#    #+#             */
/*   Updated: 2024/09/19 12:47:43 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	ft_compute_min_max(t_fdf *fdf, t_map *map)
{
	int			x;
	int			y;
	t_vector	vec;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			vec = ft_cal_vec(*map->vectors[y * map->width + x], fdf);
			if (vec.x < fdf->cam->min_x)
				fdf->cam->min_x = vec.x;
			if (vec.x > fdf->cam->max_x)
				fdf->cam->max_x = vec.x;
			if (vec.y < fdf->cam->min_y)
				fdf->cam->min_y = vec.y;
			if (vec.y > fdf->cam->max_y)
				fdf->cam->max_y = vec.y;
			x++;
		}
		y++;
	}
}

static void	ft_calculate_scale_and_offset(t_fdf *fdf)
{
	double	scale_x;
	double	scale_y;
	double	img_width;
	double	img_height;

	scale_x = (double)WIN_WIDTH / (fdf->cam->max_x - fdf->cam->min_x);
	scale_y = (double)WIN_HEIGHT / (fdf->cam->max_y - fdf->cam->min_y);
	if (scale_x < scale_y)
		fdf->cam->scale = scale_x;
	else
		fdf->cam->scale = scale_y;
	img_width = (fdf->cam->max_x - fdf->cam->min_x) * fdf->cam->scale;
	img_height = (fdf->cam->max_y - fdf->cam->min_y) * fdf->cam->scale;
	fdf->cam->offsetx = (WIN_WIDTH - img_width) / 2;
	fdf->cam->offsety = (WIN_HEIGHT - img_height) / 2;
}

static void	ft_calculate_and_adjust_to_window(t_fdf *fdf, t_map *map)
{
	ft_compute_min_max(fdf, map);
	ft_calculate_scale_and_offset(fdf);
}

static void	ft_calculate_and_draw_line(t_fdf *fdf, int x, int y)
{
	t_vector	vec1;
	t_vector	vec2;

	vec1 = ft_cal_vec(*fdf->map->vectors[y * fdf->map->width + x], fdf);
	vec1.x = (vec1.x - fdf->cam->min_x) * fdf->cam->scale + fdf->cam->offsetx;
	vec1.y = (vec1.y - fdf->cam->min_y) * fdf->cam->scale + fdf->cam->offsety;
	if (x + 1 < fdf->map->width)
	{
		vec2 = ft_cal_vec(*fdf->map->vectors[y * fdf->map->width + x + 1], fdf);
		vec2.x = (vec2.x - fdf->cam->min_x) * fdf->cam->scale + \
				fdf->cam->offsetx;
		vec2.y = (vec2.y - fdf->cam->min_y) * fdf->cam->scale + \
				fdf->cam->offsety;
		ft_line(fdf, vec1, vec2);
	}
	if (y + 1 < fdf->map->height)
	{
		vec2 = ft_cal_vec(*fdf->map->vectors[(y + 1) * fdf->map->width + x], \
				fdf);
		vec2.x = (vec2.x - fdf->cam->min_x) * fdf->cam->scale + \
				fdf->cam->offsetx;
		vec2.y = (vec2.y - fdf->cam->min_y) * fdf->cam->scale + \
				fdf->cam->offsety;
		ft_line(fdf, vec1, vec2);
	}
}

void	ft_render(t_fdf *fdf)
{
	int			x;
	int			y;

	ft_bzero(fdf->image->ptr, WIN_WIDTH * WIN_HEIGHT * fdf->image->bpp);
	ft_calculate_and_adjust_to_window(fdf, fdf->map);
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			ft_calculate_and_draw_line(fdf, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image, 0, 0);
}
