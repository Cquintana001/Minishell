/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:57:01 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/31 11:13:42 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../libft/libft.h"
#include "../includes/utils.h"
#include "../includes/executor.h"
#include "../includes/environment.h"

extern int	g_status;

static char	**ft_rm_var(char *var, char **env)
{
	char	**new_env;
	int		len;
	int		i;
	int		j;

	len = 0;
	while (env[len])
		len++;
	new_env = (char **)ft_calloc(len, sizeof(char *));
	i = 0;
	j = 0;
	while (i < (len - 1))
	{
		if ((ft_strnstr(env[j], var, ft_strlen(var)) \
			&& env[j][ft_strlen(var)] == '=' ) || \
			(ft_strnstr(env[j], var, ft_strlen(var)) \
			&& !env[j][ft_strlen(var)]))
			j++;
		new_env[i] = ft_strdup(env[j]);
		i++;
		j++;
	}
	new_env[i] = 0;
	return (new_env);
}

void	ft_unset(char *var, char ***env)
{
	char	**env2;
	char	**aux;
	int		coin;
	int		i;

	env2 = *env;
	i = 0;
	coin = 0;
	while (env2[i])
	{
		if (var && ft_strnstr(env2[i], var, ft_strlen(var)))
			if (env2[i][ft_strlen(var)] == '=' || !env2[i][ft_strlen(var)])
				coin++;
		i++;
	}
	if (coin != 0)
	{
		aux = ft_rm_var(var, env2);
		free_d_array(env2);
		*env = aux;
	}
}

void	ft_chdir(char *dir, char ***env)
{
	char	*pwd;

	if ((ft_strlen(dir) == 1 && ft_strncmp(dir, "~", 1) == 0) || !dir)
		dir = ft_getenv(*env, "HOME");
	if (access(dir, F_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_status = 1;
	}
	pwd = getcwd(NULL, 0);
	ft_export_job("OLDPWD=", pwd, env);
	free (pwd);
	chdir(dir);
	pwd = getcwd(NULL, 0);
	ft_export_job("PWD=", pwd, env);
	free (pwd);
}
