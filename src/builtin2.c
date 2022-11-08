/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:34:32 by amarzana          #+#    #+#             */
/*   Updated: 2022/11/04 08:27:57 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/executor.h"
#include "../includes/utils.h"
#include "../libft/libft.h"

static char	**ft_add_var(char *var, char *value, char **env)
{
	char	**new_env;
	int		len;
	int		i;

	len = 0;
	while (env[len])
		len++;
	new_env = (char **)ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	if (value)
		new_env[i] = ft_strjoin(var, value);
	else
		new_env[i] = ft_substr(var, 0, ft_strlen(var));
	new_env[++i] = 0;
	return (new_env);
}

static int	ft_edit_var2(char *var, char *value, char ***env, int i)
{
	char	**env2;

	env2 = *env;
	if (var && (ft_strlen(var) - 1) == ft_strlen(env2[i])
		&& var[ft_strlen(var) - 1] == '=')
	{
		if (ft_strnstr(var, env2[i], ft_strlen(env2[i])))
		{
			free(env2[i]);
			env2[i] = ft_strjoin(var, value);
			return (1);
		}
	}
	return (0);
}

static int	ft_edit_var(char *var, char *value, char ***env, int i)
{
	char	**env2;

	env2 = *env;
	if (var && ft_strnstr(env2[i], var, ft_strlen(var)))
	{
		if (value)
		{
			free(env2[i]);
			env2[i] = ft_strjoin(var, value);
			return (1);
		}
		else if (!env2[i][ft_strlen(var)] || env2[i][ft_strlen(var)] == '=')
		{
			free(env2[i]);
			env2[i] = ft_substr(var, 0, ft_strlen(var));
			return (1);
		}
	}
	return (0);
}

void	ft_export_job(char *var, char *value, char ***env)
{
	char	**env2;
	char	**aux;
	int		coin;
	int		i;

	env2 = *env;
	i = -1;
	coin = 0;
	while (env2[++i])
	{
		coin += ft_edit_var(var, value, env, i);
		coin += ft_edit_var2(var, value, env, i);
	}
	if (var && coin == 0)
	{
		aux = ft_add_var(var, value, env2);
		free_d_array(env2);
		*env = aux;
	}
}

void	ft_export(char **cmd, char ***env)
{
	char	*var;
	int		i;

	var = NULL;
	i = 1;
	if (!cmd[i])
		ft_env(*env, 1);
	while (cmd[i])
	{
		var = ft_subst_var(cmd[i]);
		if (var)
		{
			if (ft_check_var(var, cmd[0]))
				ft_export_job(var, (ft_strchr(cmd[i], '=') + 1), env);
			free(var);
			var = NULL;
		}
		else
		{
			if (ft_check_var(cmd[i], cmd[0]))
				ft_export_job(cmd[i], NULL, env);
		}
		i++;
	}
}
