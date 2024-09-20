/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:22:18 by myokono           #+#    #+#             */
/*   Updated: 2024/09/20 16:52:08 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
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
