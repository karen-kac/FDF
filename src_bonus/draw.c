/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:10 by myokono           #+#    #+#             */
/*   Updated: 2024/09/18 18:09:43 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static int	ft_line_point(t_fdf *fdf, t_line *l, t_vector *p1, t_vector *p2)
{
	double	percent;

	if (p1->x < 0 || p1->x >= WIN_WIDTH || p1->y < 0 || p1->y >= WIN_HEIGHT
		|| p2->x < 0 || p2->x >= WIN_WIDTH || p2->y < 0 || p2->y >= WIN_HEIGHT)
		return (1);
	if (l->dx > l->dy)
		percent = ft_normalize((int)p1->x, (int)l->start.x, (int)l->stop.x);
	else
		percent = ft_normalize((int)p1->y, (int)l->start.y, (int)l->stop.y);
	image_set_pixel(fdf->image, (int)p1->x, (int)p1->y, \
		ft_color(p1->color, p2->color, percent));
	l->err2 = l->err;
	if (l->err2 > -l->dx)
	{
		l->err -= l->dy;
		p1->x += l->sx;
	}

	if (l->err2 < l->dy)
	{
		l->err += l->dx;
		p1->y += l->sy;
	}
	return (0);
}

static void	ft_line(t_fdf *fdf, t_vector p1, t_vector p2)
{
	t_line	line;

	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	line.start = p1;
	line.stop = p2;
	if (!ft_lineclip(&p1, &p2))
		return ;
	line.dx = (int)ft_abs((int)p2.x - (int)p1.x);
	line.dy = (int)ft_abs((int)p2.y - (int)p1.y);
	if ((int)p1.x < (int)p2.x)
		line.sx = 1;
	else
		line.sx = -1;
	if ((int)p1.y < (int)p2.y)
		line.sy = 1;
	else
		line.sy = -1;
	if (line.dx > line.dy)
		line.err = line.dx / 2;
	else
		line.err = -line.dy / 2;
	while ((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y)
	{
		if (ft_line_point(fdf, &line, &p1, &p2))
			break ;
	}
}

// static void	ft_adjust_to_window(t_fdf *fdf, t_vector vec)
// {
// 	double		min_x, max_x, min_y, max_y;
// 	double		current_x, current_y;

// 	// 初期化
// 	min_x = DBL_MAX;
// 	max_x = -DBL_MAX;
// 	min_y = DBL_MAX;
// 	max_y = -DBL_MAX;

// 	// すべての点の変換後の座標を確認
// 	vec.y = 0;
// 	while (vec.y < fdf->map->height)
// 	{
// 		vec.x = 0;
// 		while (vec.x < fdf->map->width)
// 		{
// 			// 点の座標を取得して投影
// 			t_vector transformed_vec = ft_cal_vec(*fdf->map->vectors[(int)vec.y * fdf->map->width + (int)vec.x], fdf);
// 			current_x = transformed_vec.x;
// 			current_y = transformed_vec.y;

// 			// 最小・最大のX、Y座標を更新
// 			if (current_x < min_x)
// 				min_x = current_x;
// 			if (current_x > max_x)
// 				max_x = current_x;
// 			if (current_y < min_y)
// 				min_y = current_y;
// 			if (current_y > max_y)
// 				max_y = current_y;

// 			vec.x++;
// 		}
// 		vec.y++;
// 	}

// 	// XとYの最大・最小差を求める
// 	double x_diff = max_x - min_x;
// 	double y_diff = max_y - min_y;

// 	// ウィンドウに収めるためのスケール計算
// 	double scale_x = (double)WIN_WIDTH / x_diff;
// 	double scale_y = (double)WIN_HEIGHT / y_diff;
// 	double final_scale = scale_x < scale_y ? scale_x : scale_y;

// 	// スケールを適用 (zoomは変更しない)
// 	fdf->cam->zoom = final_scale;

// 	// オフセットを調整して中央に配置
// 	fdf->cam->offsetx = (WIN_WIDTH - (max_x + min_x) * final_scale) / 2;
// 	fdf->cam->offsety = (WIN_HEIGHT - (max_y + min_y) * final_scale) / 2;
// }

// void ft_render(t_fdf *fdf)
// {
// 	int x, y;
// 	t_vector vec;
// 	t_map *map = fdf->map;

// 	// 画面をクリア
// 	// ft_clear_image(fdf->image);

// 	y = 0;
// 	while (y < map->height)
// 	{
// 		x = 0;
// 		while (x < map->width)
// 		{
// 			vec = ft_cal_vec(map->vectors[y * map->width + x], fdf);
// 			if (x + 1 < map->width)
// 				ft_line(fdf, ft_cal_vec(*map->vectors[y * map->width + x], fdf));
// 			if (y + 1 < map->height)
// 				ft_line(fdf, ft_cal_vec(*map->vectors[y * map->width + x], fdf));
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->ptr, 0, 0);
// }



void	ft_render(t_fdf *fdf)
{
	int			x;
	int			y;
	t_map		*map;
	t_vector	vec1;
	t_vector	vec2;

	map = fdf->map;
	ft_bzero(fdf->image->ptr, WIN_WIDTH * WIN_HEIGHT * fdf->image->bpp);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{

			vec1 = ft_cal_vec(*map->vectors[y * map->width + x], fdf);
			if (x + 1 < map->width)
			{
				vec2 = ft_cal_vec(*map->vectors[y * map->width + x + 1], fdf);
				ft_line(fdf, vec1, vec2);
			}
			if (y + 1 < map->height)
			{
				vec2 = ft_cal_vec(*map->vectors[(y + 1) * map->width + x], fdf);
				ft_line(fdf, vec1, vec2);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image, 0, 0);
}
