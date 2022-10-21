/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:27:09 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/20 17:36:32 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "utils.h"
#include <stdio.h>

void	fill_cmd_path(t_data *list, char **envp)
{
	char	*path1;

	path1 = NULL;
	while (1)
	{
		if (list->cmd)
			path1 = check_if_command(envp, list->cmd[0]);
		if (path1 != 0)
			list->path = path1;
		if (list->next == NULL)
			break ;
		list = list->next;
	}
}
