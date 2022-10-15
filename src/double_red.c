/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:07:06 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/13 07:42:55 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <readline/readline.h>
#include <sys/wait.h>
#include <stdlib.h>

char	*add_line_break(char *aux, char *str)
{
	char	*array;

	array = aux;
	aux = ft_strjoin(aux, "\n");
	free(array);
	array = aux;
	aux = ft_strjoin(aux, str);
	free(array);
	return (aux);
}

void double_redirection(char *key)
{
	char	*aux;
	char	*str;

	aux = 0;
	while (1)
	{
		str = readline("> ");
		if (!ft_strncmp(str, key, __INT_MAX__))
			break ;
		if (!aux)
			aux = ft_strdup(str);
		else
			aux = add_line_break(aux, str);
		free(str);
	}
	free(str);
	write(1,aux, ft_strlen(aux));
	write(1, "\n",1);
	 free(aux);
	  exit(0);
}
