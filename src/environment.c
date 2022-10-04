/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:49:33 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/04 12:41:40 by caquinta         ###   ########.fr       */
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

	while (*env2)
	{
		if (ft_strnstr(*env2, var, ft_strlen(var)))
		{
			var1 = ft_strchr(*env2, '=');
			return (++var1);
		}
		env2++;
	}
	return (NULL);
}
