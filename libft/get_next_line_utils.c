/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:40:07 by myokono           #+#    #+#             */
/*   Updated: 2024/09/15 10:51:26 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin2(char *s1, char const *s2)
{
	char	*ptr;
	char	*start;
	size_t	len1;
	size_t	len2;

	if (!s1)
		len1 = 0;
	else
		len1 = ft_strlen2((char *)s1);
	len2 = ft_strlen2((char *)s2);
	ptr = (char *)malloc(len1 + len2 + 1);
	if (!ptr)
		return (NULL);
	start = ptr;
	while (s1 != NULL && *s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (start);
}

char	*ft_strchr2(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen2(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	free_and_null(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
