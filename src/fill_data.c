/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:54:12 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/29 10:55:00 by caquinta         ###   ########.fr       */
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
	while (tokens[x])
	{
		if (tokens[x][0] == '|' && tokens[x + 1][0] == '0')
			break ;
		if ((tokens[x][0] == '<' || tokens[x][0] == '>') && tokens[x + 2]
			&& tokens[x + 1][0] == '0')
			x += 4;
		else
		{
			len++;
			x += 2;
		}
	}
	if (len > 0)
	{
		aux->cmd = (char **)ft_calloc((len + 1), sizeof(char *));
		aux->cmd[len] = 0;
	}
}

int	sum_redirection(char **tokens, int index)
{
	if ((tokens[index][0] == '<' || tokens[index][0] == '>') && tokens[index
		+ 1][0] == '0' && tokens[index + 2])
		return (4);
	else if ((tokens[index][0] == '<' || tokens[index][0] == '>')
			&& tokens[index + 1][0] == '0' && !tokens[index + 2])
		return (2);
	return (0);
}

int	fill_commands(char **tokens, t_data *node)
{
	int	x;
	int	i;
	int	s;

	s = 0;
	i = 0;
	x = 0;
	malloc_commands(tokens, &node);
	while (tokens[x])
	{
		if (tokens[x][0] == '|' && tokens[x + 1][0] == '0')
			break ;
		s = sum_redirection(tokens, x);
		x += s;
		if (tokens[x] && s == 0)
		{
			node->cmd[i] = ft_strdup(tokens[x]);
			i++;
			x += 2;
		}
	}
	if (tokens[x] && tokens[x][0] == '|' && tokens[x + 1][0] == '0')
		return (x);
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
	while (tokens && tokens[x])
	{
		len = fill_commands(tokens + x, nodes);
		if (!len)
			break ;
		else
			nodes = nodes->next;
		x += len + 2;
	}
	return (aux);
}
