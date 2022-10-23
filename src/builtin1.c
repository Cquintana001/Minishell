/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:35:02 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/23 08:09:07 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../libft/libft.h"
#include "../includes/environment.h"
#include <stdio.h>

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

void	ft_echo(char **cmd, char **env)
{
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	if (cmd[0])
	{
		flag = ft_count_flags(cmd);
		i = flag;
		while (cmd[i])
		{
			if (ft_strncmp(cmd[i], "~", ft_strlen(cmd[i])) == 0)
				ft_putstr_fd(ft_getenv(env, "HOME"), 1);
			else
				ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
}

void	ft_env(char **env)
{
	while (*env)
	{
		ft_putendl_fd(*env, 1);
		env++;
	}
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free (pwd);
}

void	ft_chdir(char *dir, char ***env)
{
	char	*pwd;

	if (ft_strlen(dir) == 1 && ft_strncmp(dir, "~", 1) == 0)
		dir = ft_getenv(*env, "HOME");
	pwd = getcwd(NULL, 0);
	ft_export_job("OLDPWD=", pwd, env);
	free (pwd);
	chdir(dir);
	pwd = getcwd(NULL, 0);
	ft_export_job("OLDPWD=", pwd, env);
	free (pwd);
}
