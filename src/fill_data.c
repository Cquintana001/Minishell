/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:54:12 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/08 08:34:02 by caquinta         ###   ########.fr       */
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

/* t_data	*ft_lstnew1(int x)
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
} */

/* nt	malloc_redirection(char **tokens, t_data **node)
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
} */

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
		 
		if ((tokens[x][0] == '<' || tokens[x][0] == '>') && tokens[x+1])
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
		if ((tokens[x][0] == '<' || tokens[x][0] == '>')&& tokens[x+1])
			x += 2;
		else if (tokens[x])
		{
			aux->cmd[i] = ft_strdup(tokens[x]);
			i++;
			x++;
		}
	}
	if (tokens[x] && tokens[x][0] == '|')
		return (x);
	else
		return (0);
}

/* void	check_pipe(char **tokens)
{
	int	x;

	x = 0;
	while (tokens[x])
		x++;
	if (tokens[0][0] == '|' || tokens[x - 1][0] == '|')
	{
		printf("error pipe al principio o final del string\n");
		exit(0);
	}
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
} */

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
