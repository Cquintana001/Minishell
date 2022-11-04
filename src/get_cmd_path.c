/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:27:09 by caquinta          #+#    #+#             */
/*   Updated: 2022/11/04 08:03:18 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
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
		{
			if (list->cmd && !ft_is_builtin(list->cmd))
				path1 = check_if_command(envp, list->cmd[0]);
			if (path1 != 0)
				list->path = path1;
		}
		if (ft_is_builtin(list->cmd) > 0)
			list->path = NULL;
		if (list->next == NULL)
			break ;
		list = list->next;
	}
}
