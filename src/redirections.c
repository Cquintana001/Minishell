/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:26:16 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/21 16:25:08 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "redirections.h"
#include "redirections_utils.h"
#include "utils.h"
#include <stdlib.h>

int	malloc_redirection(char **tokens, t_data **node)
{
	int	index;
	int	x;
	int	len;

	len = 0;
	x = 0;
	index = 0;
	while (tokens[x])
	{
		if (tokens[x] && tokens[x][0] == '|' && tokens[x +1][0] == '0')
			break;
		if ((tokens[x][0] == '<' || tokens[x][0] == '>') && tokens[x
			+ 1][0] == '0')
			len++;
		x += 2;
	}
	if (tokens[x] && tokens[x][0] == '|'&& tokens[x +1][0] == '0')
		index = x;
	if (len > 0)
	{
		(*node)->redirection = (char **)malloc(((len * 2) + 1)
				* sizeof(char *));
		(*node)->redirection[len * 2] = 0;
	}
	return (index);
}

int	fill_redirection(char **tokens, t_data *node)
{
	int	x;
	int	index;
	int	i;

	index = malloc_redirection(tokens, &node);
	x = 0;
	i = 0;
	while (tokens[x])
	{	
		if (tokens[x] && tokens[x][0] == '|' && tokens[x +1][0] == '0')
			break;
		if ((tokens[x][0] == '<' || tokens[x][0] == '>') && tokens[x
			+ 1][0] == '0')
		{
			node->redirection[i] = ft_strdup(tokens[x]);
			node->redirection[++i] = ft_strdup(tokens[x + 2]);
			i++;
		}
		x += 2;
	}
	return (index);
}

int	check_redirection(char **tokens, int x, t_data **nodes)
{
	*nodes = put_last_node(*nodes);
	if (!fill_redirection(tokens + x, *nodes))
		return (-1);
	else
		x += fill_redirection(tokens + x, *nodes);
	ft_lstadd_back2(nodes, ft_lstnew2());
	x++;
	return (x);
}

t_data	*redirection(char **tokens)
{
	int		x;
	t_data	*nodes;
	t_data	*aux;
	int		i;

	i = -1;
	x = 0;
	check_pipe(tokens);
	nodes = ft_lstnew2();
	aux = nodes;
	x = 0;
	while (tokens[x])
	{
		nodes = put_last_node(nodes);
		i = fill_redirection(tokens + x, nodes);
		if (i == 0)
			break ;
		else
			x += i;
		ft_lstadd_back2(&aux, ft_lstnew2());
		x += 2;
	}
	return (aux);
}
