/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:22:18 by myokono           #+#    #+#             */
/*   Updated: 2024/09/18 15:07:25 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fdf_bonus.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

int	ft_free_map(t_map **map)
{
	if (map && *map)
	{
		ft_free((void **)&(*map)->vectors);
		ft_free((void **)map);
	}
	return (0);
}

int	ft_free_lst(t_list **lst)
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_free(&(*lst)->content);
		ft_free((void **)lst);
		*lst = next;
	}
	return (0);
}

int	ft_free_lst_and_map(t_list **lst, t_map **map)
{
	int	i;
	int	j;

	i = ft_free_map(map);
	j = ft_free_lst(lst);
	if (i == j)
		return (0);
	return (1);
}

int	ft_free_split(char ***split)
{
	char	**str;
	int		i;

	i = 0;
	str = *split;
	while (*str)
	{
		ft_free((void **)str);
		i++;
		str = &(*split)[i];
	}
	ft_free((void **)split);
	return (0);
}


// void	ft_free_fdf(t_fdf *fdf)
// {
// 	int	i;

// 	if (!fdf)
// 		return ;

// 	if (fdf->zbuf)
// 	{
// 		i = 0;
// 		while (i < fdf->map->height)
// 		{
// 			ft_free((void **)&fdf->zbuf[i]);
// 			i++;
// 		}
// 		ft_free((void **)&fdf->zbuf);
// 	}
// 	if (fdf->image)
// 		ft_free((void **)&fdf->image);
// 	if (fdf->map)
// 		ft_free_map(&fdf->map);
// 	if (fdf->cam)
// 		ft_free((void **)&fdf->cam);
// 	if (fdf->mouse)
// 		ft_free((void **)&fdf->mouse);
// 	if (fdf->window)
// 		mlx_destroy_window(fdf->mlx, fdf->window);
// 	if (fdf->mlx)
// 	{
// 		mlx_destroy_display(fdf->mlx);
// 		ft_free((void **)&fdf->mlx);
// 	}
// 	ft_free((void **)&fdf);
// }
