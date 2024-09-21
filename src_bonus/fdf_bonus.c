/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:29 by myokono           #+#    #+#             */
/*   Updated: 2024/09/21 13:38:06 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static void	ft_error_and_exit(char *message, t_map **map)
{
	if (map != NULL)
		ft_free_map(map);
	perror(message);
	exit (1);
}

static int	ft_is_fdf_file(const char *file)
{
	int			fd;
	const char	*ext;
	size_t		len_filename;

	ext = ".fdf";
	len_filename = ft_strlen(file);
	fd = open(file, O_RDONLY);
	if (len_filename < 4 || fd < 0)
		return (0);
	if (ft_strncmp(file + len_filename - 4, ext, 4) == 0)
	{
		close (fd);
		return (1);
	}
	else
	{
		close (fd);
		return (0);
	}
}


#include <libc.h>

__attribute__((destructor))
static void destructor() {
    system("leaks fdf_bonus");
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_fdf	*fdf;
	int		fd;

	if (argc < 2)
		ft_error_and_exit("error: not enough arguments", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || !ft_is_fdf_file(argv[1]))
		ft_error_and_exit("error: invalid file", &map);
	if (!ft_read_file(fd, &map))
		ft_error_and_exit("error: invalid file", &map);
	fdf = ft_init_fdf(ft_strjoin("FdF - ", argv[1]));
	if (fdf == NULL)
		ft_error_and_exit("error: mlx couldn't init", NULL);
	fdf->map = map;
	fdf->cam = ft_init_cam(fdf);
	if (!fdf->cam)
		ft_error_and_exit("error: mlx couldn't init", NULL);
	ft_render(fdf);
	ft_setup_controls(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
