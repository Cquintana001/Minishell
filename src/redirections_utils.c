/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:43:44 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/30 12:58:48 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "redirections.h"
#include "utils.h"
#include <stdlib.h>

t_data	*ft_lstnew2(void)
{
	t_data	*list;

	list = ft_calloc(1, sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->cmd = NULL;
	list->input = 0;
	list->output = 0;
	list->path = NULL;
	list->redirection = NULL;
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

int	check_pipe(char **tokens)
{
	int	x;

	x = 0;
	while (tokens && tokens[x])
		x++;
	if (x > 0 && (tokens[0][0] == '|') && tokens[1][0 == '0'])
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(tokens[0], 2);
		ft_putendl_fd("\'", 2);
		return (1);
	}
	else if (x > 0 && tokens[x - 2][0] == '|' && tokens[x - 1][0] == '0')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(tokens[x - 2], 2);
		ft_putendl_fd("\'", 2);
		return (2);
	}
	return (0);
}
