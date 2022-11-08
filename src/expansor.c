/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 08:54:40 by caquinta          #+#    #+#             */
/*   Updated: 2022/11/05 14:11:11 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "environment.h"
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

char	*check_var(char *var, char *first, char *second, char **env2)
{
	char	*var1;

	var1 = NULL;
	if (ft_strncmp("?", var, INT64_MAX) != 0 && ft_getenv(env2, var))
	{
		second = ft_strjoin(first, ft_getenv(env2, var));
		free(first);
		return (second);
	}
	else if (ft_strncmp("?", var, INT64_MAX) == 0)
	{
		var = ft_itoa(g_status);
		second = ft_strjoin(first, var);
		free(var);
		free(first);
		return (second);
	}
	free(first);
	return (second);
}

int	expansor_variable(char **str, int x, char **env2)
{
	char	*var;
	char	*first_part;
	char	*second_part;
	char	*aux;

	var = dollar_variable((*str + x));
	first_part = ft_substr(*str, 0, x);
	second_part = NULL;
	second_part = check_var(var, first_part, second_part, env2);
	aux = *str + x + 1 + ft_strlen(var);
	first_part = ft_strjoin(second_part, aux);
	free(second_part);
	free(*str);
	*str = first_part;
	free(var);
	return (-1);
}

char	*expansor(char *str, char **env2)
{
	int	x;
	int	i;

	i = -1;
	x = 0;
	while (str && str[x])
	{
		if (str[x] == '"' && second_char_exists(str + x, str[x]) && x > i)
			i = find_pos(str, x);
		else if (str[x] == '\'' && second_char_exists(str + x, str[x])
			&& x >= i)
			x += count_char_index(str + x, str[x]);
		if (str[x] == '$' && (str[x + 1] && str[x + 1] != '"')
			&& !check_next_char(str[x + 1]))
		{
			x = expansor_variable(&str, x, env2);
			i = -1;
		}
		x++;
	}
	return (str);
}
