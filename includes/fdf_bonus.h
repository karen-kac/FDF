/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:03 by myokono           #+#    #+#             */
/*   Updated: 2024/09/27 18:54:11 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define MIN_ZOOM 1
# define MAX_ZOOM 100

# define MOUSE_LEFT_BUTTON 1
# define MOUSE_RIGHT_BUTTON 2
# define MOUSE_THIRD_BUTTON 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define MOUSE_SCROLL_LEFT 6
# define MOUSE_SCROLL_RIGHT 7

# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124

# define NUM_PAD_0 82
# define NUM_PAD_1 83
# define NUM_PAD_2 84
# define NUM_PAD_3 85
# define NUM_PAD_4 86
# define NUM_PAD_5 87
# define NUM_PAD_6 88
# define NUM_PAD_7 89
# define NUM_PAD_8 91
# define NUM_PAD_9 92
# define NUM_PAD_PLUS 69
# define NUM_PAD_MINUS 78

# define MAIN_PAD_I 34
# define MAIN_PAD_P 35
# define MAIN_PAD_0 29
# define MAIN_PAD_1 18
# define MAIN_PAD_2 19
# define MAIN_PAD_3 20
# define MAIN_PAD_4 21
# define MAIN_PAD_5 23
# define MAIN_PAD_6 22
# define MAIN_PAD_7 26
# define MAIN_PAD_8 28
# define MAIN_PAD_9 25
# define MAIN_PAD_PLUS 24
# define MAIN_PAD_MINUS 27
# define MAIN_PAD_LESS 43
# define MAIN_PAD_MORE 47

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cam
{
	int				zoom;
	double			alpha;
	double			beta;
	double			gamma;
	float			z_divisor;
	int				offsetx;
	int				offsety;
	double			scale;
	double			min_x;
	double			min_y;
	double			max_x;
	double			max_y;
}					t_cam;

typedef struct s_vector
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_vector;
typedef struct s_map
{
	int				width;
	int				height;
	int				depth_min;
	int				depth_max;
	t_vector		**vectors;
}					t_map;
typedef struct s_mouse
{
	char			isdown;
	int				x;
	int				y;
	int				lastx;
	int				lasty;
}					t_mouse;
typedef struct s_image
{
	void			*image;
	char			*ptr;
	int				bpp;
	int				stride;
	int				endian;
}					t_image;
typedef struct s_fdf
{
	void			*mlx;
	void			*window;
	t_image			*image;
	t_map			*map;
	t_cam			*cam;
	t_mouse			*mouse;
	double			**zbuf;
}					t_fdf;
typedef struct s_line
{
	t_vector		start;
	t_vector		stop;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				err2;
}					t_line;

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_render(t_fdf *fdf);

int					ft_color(int c1, int c2, double p);

void				ft_free(void **ptr);

int					ft_free_map(t_map **map);

int					ft_free_lst(t_list **lst);

int					ft_free_lst_and_map(t_list **lst, t_map **map);

int					ft_free_split(char ***split);

t_fdf				*ft_free_fdf(t_fdf *fdf);

int					ft_hook_mousedown(int button, int x, int y, t_fdf *fdf);

int					ft_hook_mouseup(int button, int x, int y, t_fdf *fdf);

int					ft_hook_mousemove(int x, int y, t_fdf *fdf);

int					ft_hook_keydown(int key, t_fdf *fdf);

void				ft_setup_controls(t_fdf *fdf);

void				ft_image_set_pixel(t_image *image, int x, int y, int color);

t_image				*ft_del_image(t_fdf *fdf, t_image *img);

t_image				*ft_new_image(t_fdf *fdf);

t_fdf				*ft_fdf_clear(t_fdf *fdf);

t_fdf				*ft_init_fdf(char *title);

t_cam				*ft_init_cam(t_fdf *fdf);

int					ft_lineclip(t_vector *p1, t_vector *p2);

void				ft_fill_colors(t_map *map);

t_vector			ft_cal_vec(t_vector vec, t_fdf *fdf);

t_vector			*ft_get_vec(int x, int y, char *str);

t_map				*ft_get_map(int width, int height);

int					ft_read_file(int fd, t_map **map);

t_list				*ft_lstnew(void *content);

void				ft_lstadd_back(t_list **lst, t_list *new);

size_t				ft_lstcount(t_list *lst);

void				ft_lstrev(t_list **lst);

double				ft_normalize(double value, double min, double max);

int					ft_abs(int i);

void				ft_line(t_fdf *fdf, t_vector p1, t_vector p2);

void				ft_zoom(int key, t_fdf *fdf);

void				ft_move(int key, t_fdf *fdf);

int					ft_close_win(void *param);

void				ft_rotate(int key, t_fdf *fdf);

void				ft_flatten(int key, t_fdf *fdf);

void				ft_setup_controls(t_fdf *fdf);

int					ft_mouse_press(int button, int x, int y, void *param);

int					ft_mouse_release(int button, int x, int y, void *param);

int					ft_mouse_move(int x, int y, void *param);

int					ft_atoi_base(const char *str, int base);

int					ft_key_press(int key, void *param);

#endif