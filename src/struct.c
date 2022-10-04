/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:21:55 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/04 12:23:36 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "struct.h"

t_data	*ft_lstnew1(int x)
{
	t_data	*list;

	list = (t_data*)malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->cmd = NULL;
	list->redirection = NULL;
	list->path = NULL;
	list->input = x;
	list->output = x;

	list->next = NULL;
	return (list);
}