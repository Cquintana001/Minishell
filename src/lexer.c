/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:09:24 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/23 09:24:22 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "double_red.h"
#include "environment.h"
#include "executor.h"
#include "expansor.h"
#include "fd_utils.h"
#include "fill_data.h"
#include "fill_tokens.h"
#include "general_function.h"
#include "get_cmd_path.h"
#include "redirections.h"
#include "utils.h"
#include "utils2.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include "signals.h"
#include "exit.h"

int global;

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
	return (count_char_index(str, *str));
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

char	*get_str(char **env)
{
	char	*aux;
	char	*str;

	aux = ft_strjoin(ft_getenv(env, "USER"), "@minishell $ ");
	str = readline(aux);
	free(aux);
	aux = ft_strtrim(str, " ");
	free(str);
	return (aux);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*str;
	char	**tokens;
	char	**env2;
	t_data	*data;

	tokens = NULL;
	if (!argc || !argv)
		exit(0);
	argc = 0;
	argv = NULL;
	env2 = env_copy(envp);
	while (1)
	{
		ft_signals();
		str = get_str(envp);
		ft_check_rl(str, &data);
		ft_exit(str);
		if (str && *str != '\0')
		{
			add_history(str);
			global = general_function(str, &data, env2);
			if(!global)
				ft_exec(data, &env2);
			ft_lstclear1(&data);
			if (tokens)
				free_d_array(tokens);
		}
		else if(str)
			free(str);
	}
	free_d_array(env2);
	return (0);
}
