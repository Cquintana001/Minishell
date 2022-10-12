/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:43:44 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/12 14:19:34 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h" 
#include "../libft/libft.h"
#include <stdlib.h>
#include "utils.h"

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

void	check_pipe(char **tokens)
{
	int	x;

	x = 0;
	while (tokens[x])
		x++;
	if (x > 0 && (tokens[0][0] == '|' || tokens[x - 1][0] == '|'))
	{
		printf("error pipe al principio o final del string\n");
		exit(0);
	}
}
