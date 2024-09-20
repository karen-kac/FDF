/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineclip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:23 by myokono           #+#    #+#             */
/*   Updated: 2024/09/20 16:51:44 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static int	ft_region(int x, int y)
{
	int	c;

	c = 0;
	if (y >= WIN_HEIGHT)
		c |= 1;
	else if (y < 0)
		c |= 2;
	if (x >= WIN_WIDTH)
		c |= 4;
	else if (x < 0)
		c |= 8;
	return (c);
}

static void	ft_clip_xy(t_vector *vec, t_vector *p1, t_vector *p2, int rout)
{
	if (rout & 1)
	{
		vec->x = p1->x + (p2->x - p1->x) * \
				(WIN_HEIGHT - p1->y) / (p2->y - p1->y);
		vec->y = WIN_HEIGHT - 1;
	}
	else if (rout & 2)
	{
		vec->x = p1->x + (p2->x - p1->x) * -p1->y / (p2->y - p1->y);
		vec->y = 0;
	}
	else if (rout & 4)
	{
		vec->x = WIN_WIDTH - 1;
		vec->y = p1->y + (p2->y - p1->y) * \
				(WIN_WIDTH - p1->x) / (p2->x - p1->x);
	}
	else
	{
		vec->x = 0;
		vec->y = p1->y + (p2->y - p1->y) * -p1->x / (p2->x - p1->x);
	}
}

static void	ft_update_clip_point(t_vector *vec, t_vector *p, int *region)
{
	p->x = vec->x;
	p->y = vec->y;
	*region = ft_region(p->x, p->y);
}

int	ft_lineclip(t_vector *p1, t_vector *p2)
{
	t_vector	vec;
	int			r1;
	int			r2;
	int			rout;

	r1 = ft_region(p1->x, p1->y);
	r2 = ft_region(p2->x, p2->y);
	while (!(!(r1 | r2) || (r1 & r2)))
	{
		rout = 0;
		if (r1 != 0)
			rout = r1;
		else
			rout = r2;
		ft_clip_xy(&vec, p1, p2, rout);
		if (rout == r1)
			ft_update_clip_point(&vec, p1, &r1);
		else
			ft_update_clip_point(&vec, p2, &r2);
	}
	return (!(r1 | r2));
}
