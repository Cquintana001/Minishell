/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:45:40 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/29 11:45:42 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../libft/libft.h"
#include "../includes/utils.h"
#include "../includes/executor.h"

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
