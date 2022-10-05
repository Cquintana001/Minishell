/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:54:12 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/05 13:43:42 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "environment.h"
#include "expansor.h"
#include "fill_tokens.h"
#include "struct.h"
#include "utils.h"
#include "utils2.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

t_data	*ft_lstnew1(int x)
{
	t_data	*list;

	list = (t_data *)malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->cmd = NULL;
	list->redirection = NULL;
	list->path = NULL;
	list->input = x;
	list->output = x;
	return (list);
}

int	fill_redirection(char **tokens, t_data **node)
{
	int	x;
	int	len;
	int	index;
	int	i;

	i = 0;
	len = 0;
	x = 0;
	while (tokens[x] && tokens[x][0] != '|')
	{
		if (tokens[x][0] == '<' || tokens[x][0] == '>')
			len++;
		x++;
	}
	if (tokens[x][0] == '|')
		index = x;
	(*node)->redirection = (char **)ft_calloc((len * 2) + 1, sizeof(char *));
	x = 0;
	while (tokens[x] && tokens[x][0] != '|')
	{
		if (tokens[x][0] == '<' || tokens[x][0] == '>')
		{
			(*node)->redirection[i] = ft_strdup(tokens[x]);
			(*node)->redirection[i + 1] = ft_strdup(tokens[x + 1]);
		}
		x++;
	}
	return (x);
}

t_data	**cmd(char **tokens)
{
	int		x;
	int		len;
	t_data	**nodes;
	t_data **aux;

	x = 0;
	 
	while(tokens[x])
		x++;
	len = x;
	x=0;
	if (tokens[0][0] == '|' || tokens[len][0] == '|')
		exit(0);
	len = 1;
	while (tokens[x])
	{
		if (tokens[x][0] == '|')
			len++;
		x++;
	}
	nodes = (t_data **)malloc(sizeof(t_data *) * len+1);
	 aux = nodes;
	x = 0;
	nodes[len] = 0;
	while (tokens[x])
	{
		x = fill_redirection(tokens + x, &(*nodes));
		if (x == 0)
			break ;
		else
			nodes++;
	}
	x = 0;
	 
	return (aux);
}
