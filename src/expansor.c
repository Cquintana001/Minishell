/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 08:54:40 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/03 09:46:40 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	len(char *str)
{
	int	x;

	x = 0;
	str++;
	if (*str == '?' || *str == '_')
		return (1);
	while (*str && ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'Z')
			|| (*str >= 'a' && *str <= 'z') || *str == '_'))
	{
		str++;
		x++;
	}
	return (x);
}

char	*dollar_variable(char *str)
{
	char	*array;
	int		l;
	int		x;

	l = len(str);
	array = (char *)calloc((l + 1), sizeof(char));
	ft_memset(array, 'a', l);
	array[l] = 0;
	l = 0;
	x = 1;
	while (array[l])
	{
		array[l] = str[x];
		l++;
		x++;
	}
	return (array);
}

char	*expansor(char *str)
{
	int		x;
	char	*var;
	char	*first_part;
	char	*second_part;
	char	*aux;

	x = 0;
	while (str[x])
	{
		if (str[x] == '$')
		{
			var = dollar_variable((str + x));
			first_part = ft_substr(str, 0, x);
			if (getenv(var))
			{
				second_part = ft_strjoin(first_part, getenv(var));
				free(first_part);
			}
			else
				second_part = first_part;
			aux = str + x + 1 + ft_strlen(var);
			first_part = ft_strjoin(second_part, aux);
			free(second_part);
			free(str);
			str = first_part;
			free(var);
			x = -1;
		}
		x++;
	}
	return (str);
}