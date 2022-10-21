/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:35:02 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/18 16:54:11 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../libft/libft.h"
#include "../includes/environment.h"
#include <stdio.h>

void	ft_echo(char **cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (cmd[0][0] == '-')
	{
		flag = 1;
		while (cmd[0][++i])
			if (cmd[0][i] != 'n')
				flag = 0;
	}
	i = 0;
	if (flag == 1)
		i = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], 1);
		if (cmd[i])
			write(1, " ", 1);
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
	ft_export("OLDPWD=", pwd, env);
	free (pwd);
	chdir(dir);
	pwd = getcwd(NULL, 0);
	ft_export("OLDPWD=", pwd, env);
	free (pwd);
}
