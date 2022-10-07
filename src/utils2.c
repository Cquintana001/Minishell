/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 09:05:01 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/07 13:36:46 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "lexer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int	count_index(char *str)
{
	int		x;
	int		i;
	int		q;
	char	*aux;

	q = 0;
	x = 0;
	i = 0;
	while (str[x])
	{
		if (str[x] == '"' || str[x] == '\'')
		{
			aux = (str + x);
			q = count_char_index(aux, str[x]);
			i += q;
			x += q + 1;
		}
		else
		{
			x++;
			i++;
		}
	}
	return (i);
}

int	check_size(char *source)
{
	int	x;
	int	check;

	check = 0;
	if ((*source == '\'' || *source == '"'))
	{
		if (check == 0)
		{
			x = count_char_index(source, *source) - 1;
			check = 1;
		}
		else
		{
			check = 0;
			x = 0;
		}
	}
	else
		x = 1;
	return (x);
}

void	fill_array(char *source, char *dest)
{
	int	x;
	int	check;

	check = 0;
	while (*source)
	{
		x = check_size(source);
		source++;
		while (x)
		{
			*dest = *source;
			x--;
			source++;
			dest++;
		}
	}
}

int	check_quotes(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '\'' || str[x] == '"')
			return (0);
		x++;
	}
	return (1);
}

char	*erase_quotes(char *str)
{
	int		x;
	char	*array;

	if (check_quotes(str))
	{
		return (str);
	}
	x = count_index(str);
	if (x == 0 || x == -1)
		return (str);
	else
	{
		array = (char *)ft_calloc(x, sizeof(char));
		array[x - 1] = '\0';
		fill_array(str, array);
	}
	return (array);
}

/* x = 1;
		if ((*source == '\'' || *source == '"'))
		{
			if (check == 0)
			{
				x = count_char_index(source, *source) - 1;
				source++;
				check = 1;
			}
			else
			{
				source++;
				check = 0;
				x = 0;
			}
		} */