/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:49:33 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/03 11:25:49 by caquinta         ###   ########.fr       */
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

	len = ft_strlen(*env);
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
		while (*env2)
	{
		if (ft_strnstr(*env2, var, ft_strlen(var)))
			return (ft_strchr(*env2, '='));
		env2++;
	}
	return (0);
}