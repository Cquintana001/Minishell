/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:27:09 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/18 12:11:39 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "utils.h"
#include <stdio.h>

void	fill_cmd_path(t_data *list, char **envp)
{
	char	*path1;
	while (1)
	{
		path1 = check_if_command(envp, list->cmd[0]);
 
		if (path1 != 0)
			list->path = path1;
		if (list->next == NULL)
			break ;
		printf("entra en path1\n");
		list = list->next;
	}
}
