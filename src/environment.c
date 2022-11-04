/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:49:33 by caquinta          #+#    #+#             */
/*   Updated: 2022/11/04 13:12:05 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

 
char	**env_copy(char **env)
{
	int		len;
	int		x;
	char	**env2;

	len = 0;
	while (env[len])
		len++;
	env2 = (char **)ft_calloc(len + 1, sizeof(char *));
	x = 0;
	env2[len] = 0;
	while (x < len)
	{
		env2[x] = ft_strdup(env[x]);
		x++;
	}
	return (env2);
}

char	*ft_getenv(char **env2, char *var)
{
	char	*var1;
	char	*var2;
	int		x;

	x = 0;
	var2 = ft_strjoin(var, "=");
	var1 = NULL;
	while (env2[x])
	{
		 
		if (ft_strnstr(env2[x], var2, ft_strlen(var2)))
		{
				var1 = ft_strchr(env2[x], '=');
				free(var2);
				return (++var1);
		}
		x++;
	}
	free(var2);
	return ("");
}
