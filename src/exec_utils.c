/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:20:53 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/26 13:05:12 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "utils.h"
#include "builtins.h"

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
			if (!(ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 \
			&& var[i] == '=' && !var[i + 1]))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd(": `", 2);
				ft_putstr_fd(var, 2);
				ft_putendl_fd("': not a valid identifier", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	ft_call_builtin(char **cmd, char ***envp)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0)
		ft_export(cmd, envp);
	if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
		while (cmd[++i])
			if (ft_check_var(cmd[i], cmd[0]))
				ft_unset(cmd[i], envp);
	if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
		ft_chdir(cmd[1], envp);
	if (ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0)
		ft_env(*envp, 0);
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0)
		ft_pwd();
	if (ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])) == 0)
		ft_echo(&cmd[1], *envp);
}

int	ft_is_builtin(char **cmd)
{
	if (cmd)
	{
		if ((ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0 && \
			ft_strlen(cmd[0]) == 3) || \
			(ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])) == 0 && \
			ft_strlen(cmd[0]) == 4) || \
			(ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0 && \
			ft_strlen(cmd[0]) == 3))
			return (1);
		if ((ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0 && \
			ft_strlen(cmd[0]) == 6) || \
			(ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0 && \
			ft_strlen(cmd[0]) == 5) || \
			(ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0 && \
			ft_strlen(cmd[0]) == 2))
			return (2);
	}
	return (0);
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
