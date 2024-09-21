/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:22:18 by myokono           #+#    #+#             */
/*   Updated: 2024/09/21 14:33:16 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
		free(*ptr);
	*ptr = NULL;
}

int	ft_free_map(t_map **map)
{
    int i;
    int j;

    if (map && *map)
    {
        if ((*map)->vectors)
        {
            // 各 t_vector の配列を解放
            for (i = 0; i < (*map)->height; i++)
            {
                for (j = 0; j < (*map)->width; j++)
                {
                    if ((*map)->vectors[i * (*map)->width + j])
                    {
                        free((*map)->vectors[i * (*map)->width + j]);
                        (*map)->vectors[i * (*map)->width + j] = NULL;
                    }
                }
            }
            free((*map)->vectors);  // vectors 配列自体を解放
            (*map)->vectors = NULL;
        }
        free(*map);  // map 構造体を解放
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
