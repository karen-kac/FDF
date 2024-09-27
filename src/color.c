/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:06:13 by myokono           #+#    #+#             */
/*   Updated: 2024/09/27 18:34:45 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	ft_lerp(int start, int end, double p)
{
	if (start == end)
		return (start);
	return ((int)((double)start + (end - start) * p));
}

int	ft_color(int c1, int c2, double p)
{
	int	red;
	int	green;
	int	blue;

	if (c1 == c2)
		return (c1);
	red = ft_lerp((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, p);
	green = ft_lerp((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, p);
	blue = ft_lerp(c1 & 0xFF, c2 & 0xFF, p);
	return (red << 16 | green << 8 | blue);
}

static void	update_color(t_vector *tmp, t_vector *next, \
		double depth_min, double depth_max)
{
	tmp->color = ft_color(tmp->color, next->color,
			ft_normalize(tmp->z, depth_min, depth_max));
}

static void	process_vector(t_map *map, int x, int y)
{
	t_vector	*tmp;
	t_vector	*next;

	tmp = map->vectors[y * map->width + x];
	if (x + 1 < map->width)
	{
		next = map->vectors[y * map->width + (x + 1)];
		update_color(tmp, next, map->depth_min, map->depth_max);
	}
	if (y + 1 < map->height)
	{
		next = map->vectors[(y + 1) * map->width + x];
		update_color(tmp, next, map->depth_min, map->depth_max);
	}
}

void	ft_fill_colors(t_map *map)
{
	t_vector	vec;

	vec.y = 0;
	while (vec.y < map->height)
	{
		vec.x = 0;
		while (vec.x < map->width)
		{
			process_vector(map, vec.x, vec.y);
			vec.x++;
		}
		vec.y++;
	}
}
