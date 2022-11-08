/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:52:01 by amarzana          #+#    #+#             */
/*   Updated: 2022/11/07 15:05:08 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>

extern int	g_status;

int	ft_status(char *str)
{
	if (g_status == 32512)
		g_status = 127;
	if (g_status == 512)
		g_status = 0;
	if (g_status == 256)
		g_status = 1;
	if (ft_strncmp(str, "$?", 2) == 0 && ft_strlen(str) == 2)
	{
		printf("%d: command not found\n", g_status);
		add_history(str);
		free(str);
		g_status = 127;
		return (0);
	}
	return (1);
}
