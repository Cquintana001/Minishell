/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:32:15 by caquinta          #+#    #+#             */
/*   Updated: 2022/06/08 12:29:49 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	x;

	x = 0;
	while (s[x])
		x++;
	return (x);
}

int	checkline(char *array)
{
	int	z;
	int	check;

	z = 0;
	check = 0;
	while (array[z])
	{
		if (array[z] == '\n')
			return (1);
		z++;
	}
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		x;
	char	*ptr;
	int		j;

	j = 0;
	x = 0;
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	while (s1[x])
	{
		ptr[x] = s1[x];
		x++;
	}
	while (s2[j])
	{
		ptr[x] = s2[j];
		x++;
		j++;
	}
	free(s1);
	ptr[x] = '\0';
	return (ptr);
}

char	*ft_strdup(char *s)
{
	char	*array;
	int		x;

	x = ft_strlen(s);
	array = malloc(x + 1);
	x = 0;
	if (!array)
		return (NULL);
	else
	{
		x = 0;
		while (s[x])
		{
			array[x] = s[x];
			x++;
		}
		array[x] = '\0';
		return (array);
	}
}
