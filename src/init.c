/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:55 by myokono           #+#    #+#             */
/*   Updated: 2024/09/20 14:03:48 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_fdf	*ft_free_fdf(t_fdf *fdf)
{
	int	i;

	if (fdf == NULL)
		return (NULL);
	if (fdf->zbuf)
	{
		i = 0;
		while (i < fdf->map->height)
		{
			ft_free((void **)&fdf->zbuf[i]);
			i++;
		}
		ft_free((void **)&fdf->zbuf);
	}
	if (fdf->image != NULL)
		ft_del_image(fdf, fdf->image);
	if (fdf->window != NULL)
		mlx_destroy_window(fdf->mlx, fdf->window);
	if (fdf->map)
		ft_free_map(&fdf->map);
	if (fdf->cam != NULL)
		ft_free((void **)&fdf->cam);
	ft_free((void **)&fdf);
	return (NULL);
}

static int	ft_init_(t_fdf *fdf, char *title)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (0);
	fdf->window = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, title);
	if (!fdf->window)
		return (0);
	fdf->image = ft_new_image(fdf);
	if (!fdf->image)
		return (0);
	return (1);
}

static void	ft_set_cam_defaults(t_cam *cam)
{
	cam->alpha = 0;
	cam->beta = 0;
	cam->gamma = 0;
	cam->z_divisor = 1;
	cam->offsetx = 0;
	cam->offsety = 0;
	cam->scale = 1;
	cam->min_x = DBL_MAX;
	cam->max_x = -DBL_MAX;
	cam->min_y = DBL_MAX;
	cam->max_y = -DBL_MAX;
}

t_cam	*ft_init_cam(t_fdf *fdf)
{
	t_cam	*cam;

	cam = (t_cam *)malloc(sizeof(t_cam));
	if (!cam)
	{
		ft_free_fdf(fdf);
		return (NULL);
	}
	ft_bzero(cam, sizeof(t_cam));
	if (WIN_WIDTH / fdf->map->width / 2 < WIN_HEIGHT / fdf->map->height / 2)
		cam->zoom = WIN_WIDTH / fdf->map->width / 2;
	else
		cam->zoom = WIN_HEIGHT / fdf->map->height / 2;
	ft_set_cam_defaults(cam);
	return (cam);
}

t_fdf	*ft_init_fdf(char *title)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	ft_bzero(fdf, sizeof(t_fdf));
	fdf->cam = malloc(sizeof(t_cam));
	if (!fdf->cam)
		return (ft_free_fdf(fdf));
	ft_bzero(fdf->cam, sizeof(t_cam));
	if (ft_init_(fdf, title) == 0)
		return (ft_free_fdf(fdf));
	return (fdf);
}
