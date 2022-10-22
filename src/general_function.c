/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:05:35 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/22 12:54:02 by caquinta         ###   ########.fr       */
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
	int check;

	check = 0;
	while (*lst)
	{
		aux = (*lst)->next;
		if ((*lst)->cmd != NULL)
		{	
			 if(&(*lst)->cmd[0] !=&(*lst)->path  )
			 	check =1;
			free_d_array((*lst)->cmd);
		}
		if ((*lst)->path != NULL && check == 0 )
		{	
			free((*lst)->path);
		}
		if ((*lst)->redirection != NULL)
			free_d_array((*lst)->redirection);
		free(*lst);
		*lst = aux;
	}
}

int check_redirection1(char **red)
{
	int x;

	x=0;
	
	while(red != NULL && red[x])
	{
		if((red[x][0] == '<' ||red[x][0] == '>') && red[x+1] && (red[x+1][0] == '<' ||red[x+1][0] == '>'))
		{	
			x++;
			while(red[x] && (red[x][0] == '<' ||red[x][0] == '>'))
				x++;
			printf("bash: syntax error near unexpected token %s\n", red[x-1]);
			return(1);
		}
		x++;
	}
	return(0);	
}

int	general_function(char *str, t_data **data, char **env2)
{
	char	*aux;
	char	**tokens;
	int		x;

	x = 0;
	aux = expansor(str);
	tokens = fill_tokens(aux, ft_strlen(aux));
	free(aux);
	*data = redirection(tokens);
	*data = commands(tokens, *data);
	if(check_redirection1((*data)->redirection))
		return(1);
	free_d_array(tokens);
	fill_cmd_path(*data, env2);
	return(0);
}

