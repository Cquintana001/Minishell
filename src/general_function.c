/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:05:35 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/13 11:37:29 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "double_red.h"
#include "environment.h"
#include "expansor.h"
#include "fill_data.h"
#include "fill_tokens.h"
#include "get_cmd_path.h"
#include "redirections.h"
#include "utils.h"
#include "utils2.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_lstclear1(t_data **lst)
{
	t_data	*aux;

	while (*lst)
	{
		aux = (*lst)->next;
		if ((*lst)->cmd != NULL)			 
			free_d_array((*lst)->cmd);
		if ((*lst)->path != NULL)
			free((*lst)->path);
		if ((*lst)->redirection != NULL)
			free_d_array((*lst)->redirection);
		free(*lst);
		*lst = aux;
	}
}

void	general_function(char *str, t_data **data, char **env2)
{
	char	*aux;
	char	**tokens;

	aux = expansor(str);
	tokens = fill_tokens(aux, ft_strlen(aux));
	printf("%s\n", tokens[0]);
	*data = redirection(tokens);
	*data = commands(tokens, *data);
	free_d_array(tokens);
	fill_cmd_path(*data, env2);
}
