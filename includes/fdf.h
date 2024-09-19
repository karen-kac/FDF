/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:26:57 by myokono           #+#    #+#             */
/*   Updated: 2024/09/19 12:34:20 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH			1280
# define WIN_HEIGHT			720

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <float.h>
# include <stdbool.h>

typedef enum
{
	ISO,
	PARALLEL
}	t_projection;

// typedef struct			s_cam
// {
// 	t_projection		projection;
// 	int					zoom;
// 	double				alpha;
// 	double				beta;
// 	double				gamma;
// 	float				z_divisor;
// 	int					offsetx;
// 	int					offsety;
// }						t_cam;

typedef struct			s_cam
{
	t_projection		projection;
	int					zoom;
	double				alpha;
	double				beta;
	double				gamma;
	float				z_divisor;
	int					offsetx;
	int					offsety;
	double				scale;
	double				min_x;
	double				min_y;
	double				max_x;  // 追加
	double				max_y;  // 追加
}						t_cam;


typedef struct		s_vector
{
	double		x;
	double		y;
	double		z;
	int			color;
}					t_vector;

typedef struct		s_map
{
	int			width;
	int			height;
	int			depth_min;
	int			depth_max;
	t_vector	**vectors;
}					t_map;

typedef struct		s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}					t_image;

typedef struct		s_fdf
{
	void		*mlx;
	void		*window;
	t_image		*image;
	t_map		*map;
	t_cam		*cam;
	double		**zbuf;
}					t_fdf;

typedef struct		s_line
{
	t_vector	start;
	t_vector	stop;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
}					t_line;

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

// color.c
int	ft_color(int c1, int c2, double p);

void	ft_fill_colors(t_map *map);
// draw.c

void ft_render(t_fdf *fdf);

// fdf.c

// free.c
void	ft_free(void **ptr);

int	ft_free_map(t_map **map);

int	ft_free_lst(t_list **lst);

int	ft_free_lst_and_map(t_list **lst, t_map **map);

int	ft_free_split(char ***split);

// hook.c
void	ft_setup_controls(t_fdf *fdf);

// image.c
void	ft_image_set_pixel(t_image *image, int x, int y, int color);

t_image	*ft_del_image(t_fdf *fdf, t_image *img);

t_image	*ft_new_image(t_fdf *fdf);

// init.c
t_fdf	*ft_free_fdf(t_fdf *fdf);

t_fdf	*ft_init_fdf(char *title);

t_cam	*ft_init_cam(t_fdf *fdf);

//
int	ft_lineclip(t_vector *p1, t_vector *p2);

//map.c

t_vector	ft_cal_vec(t_vector vec, t_fdf *fdf);

t_vector	*ft_get_vec(int x, int y, char *str);

t_map	*ft_get_map(int width, int height);

// reader.c
int	ft_read_file(int fd, t_map **map);

// utils.c
t_list	*ft_lstnew(void *content);

void	ft_lstadd_back(t_list **lst, t_list *new);

size_t	ft_lstcount(t_list *lst);

void	ft_lstrev(t_list **lst);

double	ft_normalize(double value, double min, double max);

int	ft_abs(int i);

int	ft_atoi_base(const char *str, int base);

// line.c
void	ft_line(t_fdf *fdf, t_vector p1, t_vector p2);
///

#endif