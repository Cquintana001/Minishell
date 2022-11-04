/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:20:53 by amarzana          #+#    #+#             */
/*   Updated: 2022/11/04 08:33:30 by caquinta         ###   ########.fr       */
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

void	ft_call_builtin2(char **cmd, char ***envp)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd[0], "EXPORT", ft_strlen(cmd[0])) == 0)
		ft_export(cmd, envp);
	if (ft_strncmp(cmd[0], "UNSET", ft_strlen(cmd[0])) == 0)
		while (cmd[++i])
			if (ft_check_var(cmd[i], cmd[0]))
				ft_unset(cmd[i], envp);
	if (ft_strncmp(cmd[0], "CD", ft_strlen(cmd[0])) == 0)
		ft_chdir(cmd[1], envp);
	if (ft_strncmp(cmd[0], "ENV", ft_strlen(cmd[0])) == 0)
		ft_env(*envp, 0);
	if (ft_strncmp(cmd[0], "PWD", ft_strlen(cmd[0])) == 0)
		ft_pwd();
	if (ft_strncmp(cmd[0], "ECHO", ft_strlen(cmd[0])) == 0)
		ft_echo(&cmd[1], *envp);
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
	if (ft_strncmp(cmd[0], "$?", ft_strlen(cmd[0])) == 0)
		ft_status(cmd[0]);
	ft_call_builtin2(cmd, envp);
}

static int	ft_is_builtin2(char **cmd)
{
	if (cmd)
	{
		if ((ft_strncmp(cmd[0], "PWD", ft_strlen(cmd[0])) == 0
				&& ft_strlen(cmd[0]) == 3) || (ft_strncmp(cmd[0], "ECHO",
					ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 4)
			|| (ft_strncmp(cmd[0], "ENV", ft_strlen(cmd[0])) == 0
				&& ft_strlen(cmd[0]) == 3))
			return (1);
		if ((ft_strncmp(cmd[0], "EXPORT", ft_strlen(cmd[0])) == 0
				&& ft_strlen(cmd[0]) == 6) || (ft_strncmp(cmd[0], "UNSET",
					ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 5)
			|| (ft_strncmp(cmd[0], "CD", ft_strlen(cmd[0])) == 0
				&& ft_strlen(cmd[0]) == 2))
			return (2);
	}
	return (0);
}

int	ft_is_builtin(char **cmd)
{
	if (cmd)
	{
		if ((ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0
				&& ft_strlen(cmd[0]) == 3) || (ft_strncmp(cmd[0], "echo",
					ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 4)
			|| (ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0
				&& ft_strlen(cmd[0]) == 3) || (ft_strncmp(cmd[0], "$?",
					ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 2))
			return (1);
		if ((ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0
				&& ft_strlen(cmd[0]) == 6) || (ft_strncmp(cmd[0], "unset",
					ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 5)
			|| (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0
				&& ft_strlen(cmd[0]) == 2))
			return (2);
	}
	return (ft_is_builtin2(cmd));
}
