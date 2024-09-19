/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:06:13 by myokono           #+#    #+#             */
/*   Updated: 2024/09/18 13:06:55 by myokono          ###   ########.fr       */
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

void	ft_fill_colors(t_map *map)
{
	t_vector	vec;
	t_vector	*tmp;

	vec.y = 0;
	while (vec.y < map->height)
	{
		vec.x = 0;
		while (vec.x < map->width)
		{
			tmp = map->vectors[(int)vec.y * map->width + (int)vec.x];
			if (tmp->color != -1)
				tmp->color = tmp->color;
			else
				tmp->color = ft_color(0xFF69B4, 0x00FFFF, \
						ft_normalize(tmp->z, map->depth_min, map->depth_max));
			vec.x++;
		}
		vec.y++;
	}
}
