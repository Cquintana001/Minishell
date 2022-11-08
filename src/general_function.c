/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:05:35 by caquinta          #+#    #+#             */
/*   Updated: 2022/11/05 14:10:22 by amarzana         ###   ########.fr       */
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
#include "redirections_utils.h"
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
		{
			if (&(*lst)->cmd[0] != &(*lst)->path)
				free_d_array((*lst)->cmd);
		}
		if ((*lst)->path != NULL)
		{
			free((*lst)->path);
		}
		if ((*lst)->redirection != NULL)
			free_d_array((*lst)->redirection);
		free(*lst);
		*lst = aux;
	}
}

int	check_redirection1(char **red)
{
	int	x;

	x = 0;
	while (red != NULL && red[x])
	{
		if ((red[x][0] == '<' || red[x][0] == '>') &&
			red[x + 1] && (red[x + 1][0] == '<' || red[x + 1][0] == '>'))
		{
			x += 1;
			while (red[x] && (red[x][0] == '<' || red[x][0] == '>'))
				x += 1;
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			ft_putstr_fd(red[x - 2], 2);
			ft_putendl_fd("\'", 2);
			return (1);
		}
		else if ((red[x][0] == '<' || red[x][0] == '>') && red[x + 1] == NULL)
		{
			ft_putstr_fd("bash: syntax error near unexpected ", 2);
			ft_putstr_fd("token `newline'\n", 2);
			return (2);
		}
		x += 2;
	}
	return (0);
}

int	general_function(char *str, t_data **data, char **env2)
{
	char	*aux;
	char	**tokens;
	int		status;

	status = 0;
	aux = expansor(str, env2);
	tokens = fill_tokens(aux, ft_strlen(aux));
	if (tokens == 0)
		return (-1);
	status = check_pipe(tokens);
	if (status)
		return (status);
	free(aux);
	*data = redirection(tokens);
	*data = commands(tokens, *data);
	status = check_redirection1((*data)->redirection);
	if (status)
	{
		free_d_array(tokens);
		return (status);
	}
	free_d_array(tokens);
	fill_cmd_path(*data, env2);
	return (0);
}
