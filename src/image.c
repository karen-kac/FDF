/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:14 by myokono           #+#    #+#             */
/*   Updated: 2024/09/19 00:36:36 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_image_set_pixel(t_image *image, int x, int y, int color)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(image->ptr + ((x + y * WIN_WIDTH) * image->bpp)) = color;
}

t_image	*ft_del_image(t_fdf *fdf, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(fdf->mlx, img->image);
		ft_free((void **)&img);
	}
	return (NULL);
}

t_image	*ft_new_image(t_fdf *fdf)
{
	t_image		*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	ft_bzero(img, sizeof(t_image));
	img->image = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!(img->image))
		return (ft_del_image(fdf, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
			&img->endian);
	img->bpp /= 8;
	return (img);
}
