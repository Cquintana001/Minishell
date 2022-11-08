/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:20:53 by amarzana          #+#    #+#             */
/*   Updated: 2022/11/07 15:10:17 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "utils.h"
#include "builtins.h"
#include "status.h"
#include "executor.h"

extern int	g_status;

char	*ft_subst_var(char *var)
{
	size_t		len;

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

static void	ft_check_var2(char *var, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_status = 1;
}

int	ft_check_var(char *var, char *cmd)
{
	int	len;
	int	i;

	len = ft_strlen(var);
	i = 0;
	if (len == 1 && !ft_isalpha(var[0]))
	{
		ft_check_var2(var, cmd);
		return (0);
	}
	while (var[i] && i < len)
	{
		if (var[i] != '_' && ((!ft_isalpha(var[i]) && i == 0) || \
		!ft_isalnum(var[i])))
		{
			if (!(ft_builtncmp(cmd, "export", ft_strlen(cmd)) == 0 \
			&& var[i] == '=' && !var[i + 1]))
			{
				ft_check_var2(var, cmd);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	ft_count_nodes(t_data *node)
{
	int		node_nb;

	node_nb = 1;
	while (node->next)
	{
		node_nb++;
		node = node->next;
	}
	return (node_nb);
}
