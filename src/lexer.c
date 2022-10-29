/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:09:24 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/29 12:09:39 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "double_red.h"
#include "environment.h"
#include "executor.h"
#include "exit.h"
#include "expansor.h"
#include "fd_utils.h"
#include "fill_data.h"
#include "fill_tokens.h"
#include "general_function.h"
#include "get_cmd_path.h"
#include "redirections.h"
#include "signals.h"
#include "status.h"
#include "utils.h"
#include "utils2.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int		g_status;

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
	if (str == NULL || *str == 0)
	{
		if (*str == 0)
			free(str);
		return (NULL);
	}
	aux = ft_strtrim(str, " ");
	free(str);
	return (aux);
}

/* int	main(int argc, char *argv[], char **envp)
{
	extern int	g_status;
	char		*str;
	char		**tokens;
	char		**env2;
	t_data		*data;

	g_status = 0;
	(void)argc;
	(void)argv;
	tokens = NULL;
	data = NULL;
	env2 = env_copy(envp);
	while (1)
	{
		ft_signals();
		str = get_str(envp);
		if (str && *str != '\0' && ft_check_rl(str, &data) != -1)
		{
			ft_exit(str);
			if (str && *str != '\0' && ft_status(str))
			{
				add_history(str);
				g_status = general_function(str, &data, env2);
				if (tokens)
					free_d_array(tokens);
				if (!g_status)
					g_status = ft_exec(data, &env2);
				if (data)
					ft_lstclear1(&data);
			}
		}
		else if (str)
			free(str);
	}
	free_d_array(env2);
	return (0);
} */
