/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:32:15 by caquinta          #+#    #+#             */
/*   Updated: 2022/06/09 12:11:26 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include "get_next_line.h"
#include <limits.h>
#include <time.h>

char	*read_from_fd(int fd, char *buffer)
{
	ssize_t	nr_bytes;
	char	buf1[BUFFER_SIZE + 1];

	while (!buffer || checkline(buffer) == -1)
	{
		nr_bytes = read(fd, buf1, BUFFER_SIZE);
		if (nr_bytes <= 0 && !buffer)
		{
			free(buffer);
			return (NULL);
		}
		if (nr_bytes < 0)
			break ;
		else if (nr_bytes == 0)
			return (buffer);
		buf1[nr_bytes] = '\0';
		if (buffer)
			buffer = ft_strjoin(buffer, buf1);
		else
			buffer = ft_strdup(buf1);
	}
	return (buffer);
}

char	*get_line_to_return(char *buffer)
{
	int		z;
	int		x;
	char	*line;

	x = 0;
	z = 0;
	while (buffer[z])
	{
		if (buffer[z] == '\n')
		{
			z++;
			break ;
		}
		z++;
	}
	line = malloc(z + 1);
	while (x < z)
	{
		line[x] = buffer[x];
		x++;
	}
	line[x] = '\0';
	return (line);
}

char	*set_line(char *array)
{
	int		z;
	int		x;
	char	*temp;

	z = 0;
	while (array[z] != '\n' && array[z])
		z++;
	x = ft_strlen(array) - z;
	if (x > 1)
		temp = malloc(x);
	else
	{
		free(array);
		return (0);
	}
	x = 0;
	while (array[++z])
	{
		temp[x] = array[z];
		x++;
	}
	temp[x] = '\0';
	free(array);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*line2;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line2 = read_from_fd(fd, line2);
	if (line2 == NULL)
	{
		free(line2);
		return (NULL);
	}
	else
	{
		line = get_line_to_return(line2);
		line2 = set_line(line2);
		return (line);
	}
}

/* int main()
{
	ssize_t	fd = open("prueba.txt", O_RDONLY);
	size_t	i = 13;
	char	*line;
	while (i--)
	{
		line = get_next_line(fd);
		printf("%s",line);
		free(line);
	}
	close(fd);
	return (0);
} */
