/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:48:37 by myokono           #+#    #+#             */
/*   Updated: 2024/09/18 23:15:01 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;
	size_t	len_content;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	if (content == NULL)
	{
		new_node->content = NULL;
		new_node->content_size = 0;
	}
	else
	{
		len_content = ft_strlen(content) + 1;
		new_node->content = malloc(len_content);
		if (!new_node->content)
		{
			ft_free((void **)&new_node);
			return (NULL);
		}
		ft_memcpy(new_node->content, content, len_content);
	}
	new_node->next = NULL;
	return (new_node);
}

static t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

size_t	ft_lstcount(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstrev(t_list **lst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	prev = NULL;
	cur = *lst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*lst = prev;
}
