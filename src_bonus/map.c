/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:36 by myokono           #+#    #+#             */
/*   Updated: 2024/09/18 15:16:01 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static void	rotate_x(double *y, double *z, double alpha)
{
	double	previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

/*
** Rotate coordinate by y axis
*/

static void	rotate_y(double *x, double *z, double beta)
{
	double previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

/*
** Rotate coordinate by z axis
*/

static void	rotate_z(double *x, double *y, double gamma)
{
	double previous_x;
	double previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

/*
** Convert coordinate to iso projection
*/

static void	iso(double *x, double *y, double z)
{
	double previous_x;
	double previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

/*
** Project coordinate to 2D plane
*/

t_vector		ft_cal_vec(t_vector v, t_fdf *fdf)
{
	v.x *= fdf->cam->zoom;
	v.y *= fdf->cam->zoom;
	v.z *= fdf->cam->zoom / fdf->cam->z_divisor;
	v.x -= (fdf->map->width * fdf->cam->zoom) / 2;
	v.y -= (fdf->map->height * fdf->cam->zoom) / 2;
	rotate_x(&v.y, &v.z, fdf->cam->alpha);
	rotate_y(&v.x, &v.z, fdf->cam->beta);
	rotate_z(&v.x, &v.y, fdf->cam->gamma);
	if (fdf->cam->projection == ISO)
		iso(&v.x, &v.y, v.z);
	v.x += WIN_WIDTH / 2 + fdf->cam->offsetx;
	v.y += (WIN_HEIGHT + fdf->map->height * fdf->cam->zoom) / 2
												+ fdf->cam->offsety;
	return (v);
}


static int	ft_get_value(char c, int base)
{
	(void)base;
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (-1);
}

static int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;
	int	value;

	result = 0;
	sign = 1;
	if (base < 2 || base > 16)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	value = ft_get_value(*str, base);
	while (value != -1 && value < base)
	{
		result = result * base + value;
		str++;
		value = ft_get_value(*str, base);
	}
	return (result * sign);
}


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

