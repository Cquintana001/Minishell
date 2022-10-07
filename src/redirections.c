/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:26:16 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/07 10:49:19 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h" 
#include "../libft/libft.h"
#include <stdlib.h>
#include "utils.h"
#include "redirections_utils.h"

int	malloc_redirection(char **tokens, t_data **node)
{
	int		index;
	int		x;
	t_data	*aux1;
	int		len;
	char	**aux;

	len = 0;
	aux1 = *node;
	x = 0;
	index = 0;
	while (tokens[x] && tokens[x][0] != '|')
	{
		if (tokens[x][0] == '<' || tokens[x][0] == '>')
			len++;
		x++;
	}
	if (tokens[x] && tokens[x][0] == '|')
		index = x;
	aux = (char **)malloc(((len * 2) + 1) * sizeof(char *));
	aux1->redirection = aux;
	aux1->redirection[len * 2] = NULL;
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
	while (tokens[x] && tokens[x][0] != '|')
	{
		if (tokens[x][0] == '<' || tokens[x][0] == '>')
		{
			node->redirection[i] = ft_strdup(tokens[x]);
			node->redirection[++i] = ft_strdup(tokens[x + 1]);
			i++;
		}
		x++;
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
	ft_lstadd_back2(nodes, ft_lstnew2(NULL));
	x++;
	return (x);
}

t_data	*redirection(char **tokens)
{
	int		x;
	t_data	*nodes;
	t_data	*aux;

	x = 0;
	check_pipe(tokens);
	nodes = ft_lstnew2(NULL);
	aux = nodes;
	x = 0;
	while (tokens[x])
	{
		nodes = put_last_node(nodes);
		if (!fill_redirection(tokens + x, nodes))
			break ;
		else
			x += fill_redirection(tokens + x, nodes);
		ft_lstadd_back2(&aux, ft_lstnew2(NULL));
		x++;
	}
	return (aux);
}
