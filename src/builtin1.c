/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:35:02 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/31 10:50:17 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../libft/libft.h"
#include "../includes/environment.h"
#include <stdio.h>

extern int	g_status;

static int	ft_count_flags(char **cmd)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 0;
	j = 0;
	while (cmd[j])
	{
		if (cmd[j][0] == '-')
		{
			flag++;
			i = 0;
			while (cmd[j][++i])
			{
				if (cmd[j][i] != 'n')
				{
					flag--;
					return (flag);
				}
			}
		}
		j++;
	}
	return (flag);
}

static void	ft_echo_job(char **cmd, char **env, int i)
{
	while (cmd[i])
	{
		if (cmd[i][0] == '~' && ft_strlen(cmd[i]) == 1)
			ft_putstr_fd(ft_getenv(env, "HOME"), 1);
		else if (ft_strncmp(cmd[i], "~/", ft_strlen(cmd[i])) == 0 \
			&& ft_strlen(cmd[i]) == 2)
		{
			ft_putstr_fd(ft_getenv(env, "HOME"), 1);
			write(1, "/", 1);
		}
		else if (ft_strncmp(cmd[i], "$?", ft_strlen(cmd[i])) == 0 \
			&& ft_strlen(cmd[i]) == 2)
			ft_putnbr_fd(g_status, 1);
		else
			ft_putstr_fd(cmd[i], 1);
		if (cmd[i++ + 1])
			write(1, " ", 1);
	}
}
void	ft_echo(char **cmd, char **env)
{
	int		flag;

	flag = ft_count_flags(cmd);
	ft_echo_job(cmd, env, flag);
	if (flag == 0)
		write(1, "\n", 1);
}

void	ft_env(char **env, int mode)
{
	char	*var;

	var = NULL;
	if (mode == 0)
	{
		while (*env)
		{
			var = ft_subst_var(*env);
			if (var)
			{
				ft_putendl_fd(*env, 1);
				free (var);
			}
			env++;
		}
	}
	else
	{
		while (*env)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd(*env, 1);
			env++;
		}
	}
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free (pwd);
}
