/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:09:24 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/05 13:32:03 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "environment.h"
#include "expansor.h"
#include "fill_data.h"
#include "fill_tokens.h"
#include "struct.h"
#include "utils.h"
#include "utils2.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	count_char_index(char *str, char a)
{
	int	x;

	str++;
	x = 1;
	while (*str)
	{
		if (*str == a)
			return (x);
		str++;
		x++;
	}
	return (-1);
}
int	count_word_index(char *str)
{
	int	x;
	int	i;

	i = 0;
	x = 0;
	while (*str)
	{
		if ((*str == '"' || *str == '\''))
		{
			if (!second_char_exists(str, *str))
			{
				printf("error\n");
				return (-1);
			}
			i = count_char_index(str, *str);
			x += i + 1;
			str += i + 1;
		}
		else if (*str == '|' || *str == '<' || *str == '>' || *str == ' ')
			return (x);
		else
		{
			x++;
			str++;
		}
	}
	return (x);
}

int	count_tokens(char *str)
{
	int	num_token;
	int	index;

	index = 0;
	num_token = 0;
	while (*str)
	{
		if (*str == '|' || *str == '<' || *str == '>')
			num_token++;
		else if (*str != ' ')
		{
			index = count_word_index(str);
			if (index < 0)
				return (0);
			str += index - 1;
			num_token++;
		}
		str++;
	}
	return (num_token);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*str;
	int		x;
	char	*aux;
	char	**tokens;
	char	**env2;
	t_data	*data;

	argc = 0;
	argv = NULL;
	env2 = env_copy(envp);
	while (1)
	{
		aux = ft_strjoin(ft_getenv(env2, "USER"), "@minishell $ ");
		str = readline(aux);
		add_history(str);
		if (!str)
			continue ;
		free(aux);
		aux = expansor(str);
		tokens = fill_tokens(aux, x);
		x = 0;
		while (tokens[x])
		{
			printf("token[%d]: %s\n", x, tokens[x]);
			x++;
		}
		//free(aux);
		printf("entra\n");
		data = cmd(tokens);
		printf("entra2\n");
		x = 0;
		printf("entra %s\n", data->redirection[x]);
		while (data->redirection[x])
		{
			printf("str es %s\n", data->redirection[x]);
			x++;
		}
	}
	free_d_array(tokens);
	return (0);
}
