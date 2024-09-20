/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:20:30 by myokono           #+#    #+#             */
/*   Updated: 2024/09/20 20:26:48 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_sublen(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (*str == c)
		str++;
	while (str[len] != '\0' && str[len] != c)
		len++;
	return (len);
}

static size_t	ft_count_substr(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	reset;

	i = 0;
	count = 0;
	reset = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && reset == 0)
		{
			count++;
			reset++;
		}
		if (s[i] == c)
			reset = 0;
		i++;
	}
	return (count);
}

static char	*ft_substr_split(char const *s, unsigned int start, char c)
{
	size_t	i;
	size_t	sublen;
	char	*res;

	i = 0;
	if (s == NULL || s[start] == '\0')
		return (NULL);
	sublen = ft_sublen(&s[start], c);
	res = malloc(sizeof(char) * (sublen + 1));
	if (res == NULL)
		return (NULL);
	while (s[start] == c)
		start++;
	while (i < sublen && (s[start + i] != '\0' && s[start + i] != c))
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	if (s[start + i] != '\0' && s[start + i] != c)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_count_substr(s, c) + 1));
	if (res == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (s[i + 1] != c && s[i] == c && \
				s[i + 1] != '\0'))
			res[j++] = ft_substr_split(s, i, c);
		i++;
	}
	res[j] = NULL;
	return (res);
}
