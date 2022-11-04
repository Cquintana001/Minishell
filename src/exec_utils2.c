/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:20:53 by amarzana          #+#    #+#             */
/*   Updated: 2022/11/04 08:03:56 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtins.h"
#include "executor.h"
#include "status.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

extern int	g_status;

char	*ft_subst_var(char *var)
{
	size_t	len;

	len = 0;
	if (var)
	{
		while (var[len] && var[len] != '=')
			len++;
		if (len < ft_strlen(var))
			return (ft_substr(var, 0, len + 1));
	}
	return (0);
}

int	ft_check_var(char *var, char *cmd)
{
	int	len;
	int	i;

	len = ft_strlen(var);
	i = 0;
	while (var[i] && i < len)
	{
		if (!ft_isalnum(var[i]))
		{
			if (!(ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0
					&& var[i] == '=' && !var[i + 1]))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd(": `", 2);
				ft_putstr_fd(var, 2);
				ft_putendl_fd("': not a valid identifier", 2);
				g_status = 1;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	ft_count_nodes(t_data *node)
{
	int	node_nb;

	node_nb = 1;
	while (node->next)
	{
		node_nb++;
		node = node->next;
	}
	return (node_nb);
}
