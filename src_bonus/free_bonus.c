/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:22:18 by myokono           #+#    #+#             */
/*   Updated: 2024/09/27 18:44:27 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
		free(*ptr);
	*ptr = NULL;
}

static void	ft_free_vectors_rec(t_vector **vectors, int index, int total_size)
{
	if (index >= total_size)
		return ;
	if (vectors[index])
	{
		free(vectors[index]);
		vectors[index] = NULL;
	}
	ft_free_vectors_rec(vectors, index + 1, total_size);
}

int	ft_free_map(t_map **map)
{
	int	total_size;

	if (map && *map)
	{
		if ((*map)->vectors)
		{
			total_size = (*map)->height * (*map)->width;
			ft_free_vectors_rec((*map)->vectors, 0, total_size);
			free((*map)->vectors);
			(*map)->vectors = NULL;
		}
		free(*map);
		*map = NULL;
	}
	return (0);
}

int	ft_free_lst(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		if (current->content)
		{
			free(current->content);
			current->content = NULL;
		}
		free(current);
		current = next;
	}
	*lst = NULL;
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
