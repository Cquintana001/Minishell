/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:54:12 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/13 08:47:49 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "environment.h"
#include "expansor.h"
#include "fill_tokens.h"
#include "utils.h"
#include "utils2.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

void	malloc_commands(char **tokens, t_data **node)
{
	int		x;
	int		len;
	t_data	*aux;

	aux = *node;
	len = 0;
	x = 0;
	while (tokens[x] && tokens[x][0] != '|')
	{
		if ((tokens[x][0] == '<' || tokens[x][0] == '>') && tokens[x + 1])
			x += 2;
		else
		{
			len++;
			x++;
		}
	}
	aux->cmd = (char **)malloc((len + 1) * sizeof(char *));
	aux->cmd[len] = 0;
}

int	fill_commands(char **tokens, t_data *node)
{
	int		x;
	t_data	*aux;
	int		i;

	i = 0;
	x = 0;
	aux = node;
	malloc_commands(tokens, &node);
	while (tokens[x] && tokens[x][0] != '|')
	{
		if ((tokens[x][0] == '<' || tokens[x][0] == '>') && tokens[x + 1])
			x += 2;
		else if (tokens[x])
		{
			aux->cmd[i] = ft_strdup(tokens[x]);
			printf("cmd es %s\n", aux->cmd[i]);
			i++;
			x++;
		}
	}
	if (tokens[x] && tokens[x][0] == '|')
		return (x);
	else
		return (0);
}

t_data	*commands(char **tokens, t_data *aux)
{
	int		x;
	t_data	*nodes;
	int		len;

	len = 0;
	x = 0;
	nodes = aux;
	while (tokens[x])
	{
		len = fill_commands(tokens + x, nodes);
		if (!len)
			break ;
		else
			nodes = nodes->next;
		x += len + 1;
	}
	return (aux);
}
