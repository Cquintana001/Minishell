/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 08:54:40 by caquinta          #+#    #+#             */
/*   Updated: 2022/11/03 10:11:57 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "exit.h"
#include "expansor_utils.h"
#include "lexer.h"
#include "utils.h"
#include "utils2.h"
#include <stdio.h>
#include <stdlib.h>
extern int	g_status;

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

int	find_pos(char *str, int x)
{
	int	i;

	i = x + 1;
	while (str[i])
	{
		if (str[i] == str[x])
			return (i);
		i++;
	}
	return (-1);
}

char *check_var(char *var, char *first, char *second)
{
	char *var1;
	
	var1 = NULL;
	if (ft_getenv2(var))
	{
		second = ft_strjoin(first, ft_getenv2(var));
		free(first);
	}
	else if (ft_strncmp("?", var, INT64_MAX) == 0)
	{
		var = ft_itoa(g_status);
		second = ft_strjoin(first, var);
		free(var);
		free(first);
	}
	return(second);
	
}
int	expansor_variable(char **str, int x)
{
	char	*var;
	char	*first_part;
	char	*second_part;
	char	*aux;

	var = dollar_variable((*str + x));
	first_part = ft_substr(*str, 0, x);
	second_part = NULL;
	/* if (ft_getenv2(var) || ft_strncmp("?", var, INT64_MAX) == 0)
	{
		second_part = ft_strjoin(first_part, ft_getenv2(var));
		free(first_part);
	}
	else if (ft_strncmp("?", var, INT64_MAX) == 0)
	{
		second_part = ft_strjoin(first_part, ft_itoa(g_status));
		free(first_part);
	} */
	second_part = check_var(var, first_part, second_part);
	/* else
		second_part = first_part; */
	aux = *str + x + 1 + ft_strlen(var);
	first_part = ft_strjoin(second_part, aux);
	free(second_part);
	free(*str);
	*str = first_part;
	free(var);
	return (-1);
}

char	*expansor(char *str)
{
	int	x;
	int	i;

	i = -1;
	x = 0;
	while (str[x])
	{
		if (str[x] == '"' && second_char_exists(str + x, str[x]) && x > i)
			i = find_pos(str, x);
		else if (str[x] == '\'' && second_char_exists(str + x, str[x])
			&& x >= i)
			x += count_char_index(str + x, str[x]);
		if (str[x] == '$' && (str[x + 1] && str[x + 1] != '"')
			&& !check_next_char(str[x + 1]))
		{
			x = expansor_variable(&str, x);
			i = -1;
		}
		x++;
	}
	return (str);
}
