/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:40:04 by myokono           #+#    #+#             */
/*   Updated: 2024/09/15 10:52:42 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **stored)
{
	char	*line;
	int		copy_len;
	int		i;

	if (ft_strchr2(*stored, '\n') == NULL)
		copy_len = ft_strlen2(*stored);
	else
		copy_len = ft_strchr2(*stored, '\n') - *stored + 1;
	line = malloc(copy_len + 1);
	if (!line)
	{
		free_and_null(stored);
		return (NULL);
	}
	i = 0;
	while (i < copy_len)
	{
		line[i] = (*stored)[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	update_stored(char **stored)
{
	char	*new_stored;
	int		i;
	int		j;
	int		cut_len;

	if (ft_strchr2(*stored, '\n') == NULL)
		return (0);
	cut_len = ft_strchr2(*stored, '\n') - *stored + 1;
	new_stored = malloc(ft_strlen2(*stored) - cut_len + 1);
	if (!new_stored)
		return (-1);
	i = 0;
	j = cut_len;
	while ((*stored)[j])
		new_stored[i++] = (*stored)[j++];
	new_stored[i] = '\0';
	free_and_null(stored);
	*stored = new_stored;
	return (1);
}

static int	append_read_data(int fd, char **stored, char *buffer)
{
	char	*temp;
	ssize_t	read_len;

	read_len = 1;
	while (!ft_strchr2(*stored, '\n') && read_len != 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == -1)
			return (-1);
		if (read_len == 0)
			return (0);
		buffer[read_len] = '\0';
		temp = *stored;
		*stored = ft_strjoin2(temp, buffer);
		free(temp);
	}
	return (1);
}

static int	read_and_store(int fd, char **stored)
{
	char	*buffer;
	int		flag;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	flag = append_read_data(fd, stored, buffer);
	free(buffer);
	return (flag);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;
	int			flag;

	if (fd < 0 || BUFFER_SIZE <= 0 || OPEN_MAX < fd)
		return (NULL);
	flag = read_and_store(fd, &stored);
	if (flag == -1 || (flag == 0 && (!stored || *stored == '\0')))
	{
		free_and_null(&stored);
		return (NULL);
	}
	line = extract_line(&stored);
	flag = update_stored(&stored);
	if (flag == -1 || flag == 0)
		free_and_null(&stored);
	if (flag == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	char *test = "";
// 	int fd = open("test1.txt", O_RDONLY);
// 	test = get_next_line(fd);
// 	while (test)
// 	{
// 		printf("fd=%s", test);
// 		free(test);
// 		test = get_next_line(fd);
// 	}
// 	free(test);
// 	close(fd);
// }

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q a.out");
// }
// /*
// cc get_next_line.c get_next_line_uti
// ls.c get_next_line.h -Wall -Wextra -Werror
//  -D BUFFER_SIZE=4 && ./a.out |cat -e
// git clone https://github.com/Tripouille/gnlTester.git
// */