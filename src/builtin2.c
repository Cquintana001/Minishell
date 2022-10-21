/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:34:32 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/17 17:15:38 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../libft/libft.h"
#include "../includes/utils.h"

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
		if (ft_strnstr(env[j], var, ft_strlen(var)))
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
			if (env2[i][ft_strlen(var)] == '=')
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
	new_env[i] = ft_strjoin(var, value);
	new_env[++i] = 0;
	return (new_env);
}

void	ft_export(char *var, char *value, char ***env)
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
		if (var && ft_strnstr(env2[i], var, ft_strlen(var)))
		{
			free (env2[i]);
			env2[i] = ft_strjoin(var, value);
			coin++;
		}
	}
	if (var && coin == 0)
	{	
		aux = ft_add_var(var, value, env2);
		free_d_array(env2);
		*env = aux;
	}
}

