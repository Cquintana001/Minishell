/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:54:12 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/06 10:34:44 by caquinta         ###   ########.fr       */
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

int	fill_redirection(char **tokens, t_data *node)
{
	int		x;
	int		len;
	int		index;
	int		i;
	t_data	*aux1;
	char	**aux;

	aux1 = node;
	i = 0;
	len = 0;
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
	x = 0;
	while (tokens[x] && tokens[x][0] != '|')
	{
		if (tokens[x][0] == '<' || tokens[x][0] == '>')
		{
			aux1->redirection[i] = ft_strdup(tokens[x]);
			aux1->redirection[++i] = ft_strdup(tokens[x + 1]);
			i++;
		}
		x++;
	}
	return (index);
}
int	fill_commands(char **tokens, t_data *node)
{
	int		x;
	t_data	*aux;
	int		i;
	int		len;

	len = 0;
	i = 0;
	aux = node;
	x = 0;
	while (tokens[x] && tokens[x][0] != '|')
	{
		if (tokens[x][0] == '<' || tokens[x][0] == '>')
		{
			x += 2;
		}
		else
		{
			len++;
			x++;
		}
	}
	aux->cmd = (char **)malloc((len + 1) * sizeof(char *));
	aux->cmd[len] = 0;
	x = 0;
	while (tokens[x] && tokens[x][0] != '|')
	{
		if (tokens[x][0] == '<' || tokens[x][0] == '>')
			x += 2;
		else if (tokens[x])
		{	aux->cmd[i] = ft_strdup(tokens[x]);
		i++;
		x++;
		}
		printf("x es: %d\n", x);
	}
	printf("str pos es %d\n", x);
	if (tokens[x] && tokens[x][0] == '|')
		return (x);
	else
		return (0);
}

t_data	*cmd(char **tokens)
{
	int		x;
	int		len;
	t_data	*nodes;
	t_data	*aux;

	x = 0;
	while (tokens[x])
		x++;
	len = x;
	x = 0;
	if (tokens[0][0] == '|' || tokens[len - 1][0] == '|')
	{
		printf("error pipe al principio o final del string\n");
		exit(0);
	}
	len = 1;
	while (tokens[x])
	{
		if (tokens[x][0] == '|')
			len++;
		x++;
	}
	nodes = ft_lstnew2(NULL);
	aux = nodes;
	x = 0;
	while (tokens[x])
	{
		while (1)
		{
			if (nodes->next == NULL)
				break ;
			nodes = nodes->next;
		}
		if (!fill_redirection(tokens + x, nodes))
			break ;
		else
			x += fill_redirection(tokens + x, nodes);
		ft_lstadd_back2(&aux, ft_lstnew2(NULL));
		x++;
	}
	x = 0;
	nodes = aux;
	while (tokens[x])
	{
		len = fill_commands(tokens + x, nodes);
		printf("len es %d y x es %d\n", len, x);
		if (!len)
			break ;
		else
			nodes = nodes->next;
		x += len + 1;
	}
	return (aux);
}
