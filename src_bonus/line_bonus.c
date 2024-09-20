/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:09:51 by myokono           #+#    #+#             */
/*   Updated: 2024/09/20 16:54:00 by myokono          ###   ########.fr       */
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
	ft_image_set_pixel(fdf->image, (int)p1->x, (int)p1->y, \
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

static void	ft_init_line(t_line *line, t_vector *p1, t_vector *p2)
{
	line->dx = (int)ft_abs((int)p2->x - (int)p1->x);
	line->dy = (int)ft_abs((int)p2->y - (int)p1->y);
	if ((int)p1->x < (int)p2->x)
		line->sx = 1;
	else
		line->sx = -1;
	if ((int)p1->y < (int)p2->y)
		line->sy = 1;
	else
		line->sy = -1;
	if (line->dx > line->dy)
		line->err = line->dx / 2;
	else
		line->err = -line->dy / 2;
}

static void	ft_draw_line_loop(t_fdf *fdf, t_line *line, \
		t_vector *p1, t_vector *p2)
{
	while ((int)p1->x != (int)p2->x || (int)p1->y != (int)p2->y)
	{
		if (ft_line_point(fdf, line, p1, p2))
			break ;
	}
}

void	ft_line(t_fdf *fdf, t_vector p1, t_vector p2)
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
	ft_init_line(&line, &p1, &p2);
	ft_draw_line_loop(fdf, &line, &p1, &p2);
}
