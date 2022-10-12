/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:09:24 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/12 09:39:12 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "environment.h"
#include "expansor.h"
#include "fill_data.h"
#include "fill_tokens.h"
#include "redirections.h"
#include "utils.h"
#include "utils2.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_cmd_path.h"
#include "double_red.h"

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

int	count_index2(char *str)
{
	 
	if (!second_char_exists(str, *str))
	{
		printf("error\n");
		exit(0);
	}
	return (count_char_index(str, *str) );
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
			i = count_index2(str);
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
	t_data	*aux3;
	int		i;
	if(!argc || !argv)
		exit(0);
	argc = 0;
	argv = NULL;
	env2 = env_copy(envp);
	while (1)
	{
		aux = ft_strjoin(ft_getenv(env2, "USER"), "@minishell $ ");
		str = readline(aux);
		if (!str || *str == '\t' || *str == ' ')
			continue ;
		add_history(str);
		if (!str)
			continue ;
		free(aux);
		aux = expansor(str);
	 	x = 0;
		while(aux[x])
			x++;
		if(x==0)
			continue;
	 
		tokens = fill_tokens(aux, x);
		x = 0;
		 
		while (tokens[x])
		{
			printf("token[%d]: %s\n", x, tokens[x]);
			x++;
		}
		//free(aux);
		data = commands(tokens, redirection(tokens));
		i = 0;
		aux3 = data;
		fill_cmd_path(aux3, env2);
		while(1)
		{
				 
			 
				printf("path %d es %s\n",i, data->path);
				 
			 
			if (data->next == NULL)
				break ;
			data = data->next;
			i++;

			
		}
		i = 0;
		data = aux3;
		while (1)
		{
			x = 0;
			while (data->redirection[x] != NULL)
			{
				printf("redireccion %d   es %s\n", i, data->redirection[x]);
				x++;
			}
			if (data->next == NULL)
				break ;
			data = data->next;
			i++;
		}
		i = 0;
		while (1)
		{
			x = 0;
			while (aux3->cmd[x] != NULL)
			{
				printf("comando %d  es %s\n", i, aux3->cmd[x]);
				x++;
			}
			if (aux3->next == NULL)
				break ;
			aux3 = aux3->next;
			i++;
		}
		double_redirection("hola");
	}
	
	free_d_array(tokens);
	return (0);
}
