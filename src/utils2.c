/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 09:05:01 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/06 14:27:06 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "lexer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

t_data	*ft_lstnew2(void *content)
{
	t_data	*list;

	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->cmd = content;
	list->input = 0;
	list->output = 0;
	list->path = content;
	list->redirection = content;
	list->next = NULL;
	return (list);
}

t_data	*ft_lstlast2(t_data *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back2(t_data **lst, t_data *new)
{
	t_data	*last;

	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_lstlast2(*lst);
		last->next = new;
		printf("el puntero en funcion es: %p\n", last->next);
	}
}

t_data	*put_last_node(t_data *nodes)
{
	while (1)
	{
		if (nodes->next == NULL)
			break ;
		nodes = nodes->next;
	}
	return (nodes);
}
int	count_index(char *str)
{
	int		x;
	int		i;
	int		q;
	char	*aux;

	q = 0;
	x = 0;
	i = 0;
	while (str[x])
	{
		if (str[x] == '"' || str[x] == '\'')
		{
			aux = (str + x);
			q = count_char_index(aux, str[x]);
			i += q;
			x += q + 1;
		}
		else
		{
			x++;
			i++;
		}
	}
	return (i);
}
void	fill_array(char *source, char *dest)
{
	int	x;
	int	check;

	check = 0;
	while (*source)
	{
		x = 1;
		if ((*source == '\'' || *source == '"'))
		{
			if (check == 0)
			{
				x = count_char_index(source, *source) - 1;
				source++;
				check = 1;
			}
			else
			{
				source++;
				check = 0;
				x = 0;
			}
		}
		while (x)
		{
			*dest = *source;
			x--;
			source++;
			dest++;
		}
	}
}
int	check_quotes(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '\'' || str[x] == '"')
			return (0);
		x++;
	}
	return (1);
}

char	*erase_quotes(char *str)
{
	int x;
	char *array;
	if (check_quotes(str))
	{
		return (str);
	}
	x = count_index(str);
	if (x == 0 || x == -1)
		return (str);
	else
	{
		array = (char *)ft_calloc(x, sizeof(char));
		array[x - 1] = '\0';
		fill_array(str, array);
	}

	return (array);
}