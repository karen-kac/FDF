/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:16:49 by myokono           #+#    #+#             */
/*   Updated: 2024/09/21 15:32:54 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static size_t	ft_countwords(char *str, char sep)
{
	size_t	result;
	size_t	i;

	i = 0;
	result = 0;
	while (str[i] && str[i] == sep)
		i++;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		while (str[i] && str[i] != sep)
			i++;
		result++;
		while (str[i] && str[i] == sep)
			i++;
	}
	return (result);
}

static int	ft_get_lines(int fd, t_list **lst)
{
	t_list	*tmp;
	int		expected;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	expected = (int)ft_countwords(line, ' ');
	while (line)
	{
		if (expected != (int)ft_countwords(line, ' '))
		{
			ft_free((void **)&line);
			return (ft_free_lst(lst));
		}
		tmp = ft_lstnew(line);
		if (!tmp)
			return (ft_free_lst(lst));
		ft_lstadd_back(lst, tmp);
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
	return (expected);
}

static void	ft_find_depth(t_map *map)
{
	int			min;
	int			max;
	t_vector	vec;
	t_vector	tmp;

	min = INT_MAX;
	max = INT_MIN;
	vec.y = 0;
	while (vec.y < map->height)
	{
		vec.x = 0;
		while (vec.x < map->width)
		{
			tmp = *map->vectors[(int)vec.y * map->width + (int)vec.x];
			if (tmp.z < min)
				min = tmp.z;
			if (tmp.z > max)
				max = tmp.z;
			vec.x++;
		}
		vec.y++;
	}
	map->depth_min = min;
	map->depth_max = max;
}

static int	ft_3d_map(t_map **map, t_list *list)
{
	t_list	*lst;
	char	**split;
	int		x;
	int		y;

	lst = list;
	y = 0;
	while (y < (*map)->height)
	{
		x = 0;
		split = ft_split(lst->content, ' ');
		if (split == NULL)
			return (ft_free_lst_and_map(&list, map));
		while (x < (*map)->width)
		{
			(*map)->vectors[y * (*map)->width + x] = ft_get_vec(x, y, split[x]);
			x++;
		}
		ft_free_split(&split);
		lst = lst->next;
		y++;
	}
	ft_find_depth(*map);
	ft_fill_colors(*map);
	return (1);
}

int	ft_read_file(int fd, t_map **map)
{
	int		expected;
	int		i;
	t_list	*lst;

	lst = NULL;
	expected = ft_get_lines(fd, &lst);
	if (expected == 0)
		return (0);
	*map = ft_get_map(expected, ft_lstcount(lst));
	if (*map == NULL)
		return (ft_free_lst_and_map(&lst, map));
	i = ft_3d_map(map, lst);
	if (i == 1)
		ft_free_lst(&lst);
	return (i);
}
