/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:36 by myokono           #+#    #+#             */
/*   Updated: 2024/09/20 17:01:52 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

t_vector	*ft_get_vec(int x, int y, char *str)
{
	t_vector	*vec;
	char		**split;

	vec = malloc(sizeof(t_vector));
	if (!vec)
		return (NULL);
	ft_bzero(vec, sizeof(t_vector));
	vec->x = (double)x;
	vec->y = (double)y;

	if (ft_strchr(str, ','))
	{
		split = ft_split(str, ',');
		vec->z = (double)ft_atoi(split[0]);
		vec->color = ft_atoi_base(split[1] + 2, 16);
		ft_free_split(&split);
	}
	else
	{
		vec->z = (double)ft_atoi(str);
		vec->color = -1;
	}
	return (vec);
}


t_map	*ft_get_map(int width, int height)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	ft_bzero(map, sizeof(t_map));
	map->width = width;
	map->height = height;
	map->depth_min = 0;
	map->depth_max = 0;
	map->vectors = malloc(sizeof(t_vector *) * width * height);
	if (map->vectors == NULL)
	{
		ft_free((void **)&map);
		return (NULL);
	}
	ft_bzero(map->vectors, sizeof(t_vector *) * width * height);
	return (map);
}

