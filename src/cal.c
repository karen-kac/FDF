/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:43:03 by myokono           #+#    #+#             */
/*   Updated: 2024/09/19 12:47:23 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	ft_rotate_x(double *y, double *z, double alpha)
{
	double	prev_y;

	prev_y = *y;
	*y = prev_y * cos(alpha) + *z * sin(alpha);
	*z = -prev_y * sin(alpha) + *z * cos(alpha);
}

static void	ft_rotate_y(double *x, double *z, double beta)
{
	double	pre_x;

	pre_x = *x;
	*x = pre_x * cos(beta) + *z * sin(beta);
	*z = -pre_x * sin(beta) + *z * cos(beta);
}

static void	ft_rotate_z(double *x, double *y, double gamma)
{
	double	pre_x;
	double	prev_y;

	pre_x = *x;
	prev_y = *y;
	*x = pre_x * cos(gamma) - prev_y * sin(gamma);
	*y = pre_x * sin(gamma) + prev_y * cos(gamma);
}

static void	ft_iso(double *x, double *y, double z)
{
	double	pre_x;
	double	pre_y;

	pre_x = *x;
	pre_y = *y;
	*x = (pre_x - pre_y) * cos(0.523599);
	*y = -z + (pre_x + pre_y) * sin(0.523599);
}

t_vector	ft_cal_vec(t_vector vec, t_fdf *fdf)
{
	vec.x *= fdf->cam->zoom;
	vec.y *= fdf->cam->zoom;
	vec.z *= fdf->cam->zoom / fdf->cam->z_divisor;
	vec.x -= (fdf->map->width * fdf->cam->zoom) / 2;
	vec.y -= (fdf->map->height * fdf->cam->zoom) / 2;
	ft_rotate_x(&vec.y, &vec.z, fdf->cam->alpha);
	ft_rotate_y(&vec.x, &vec.z, fdf->cam->beta);
	ft_rotate_z(&vec.x, &vec.y, fdf->cam->gamma);
	ft_iso(&vec.x, &vec.y, vec.z);
	return (vec);
}
