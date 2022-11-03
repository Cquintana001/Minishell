/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:09:24 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/31 11:59:09 by amarzana         ###   ########.fr       */
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
#include "lexer.h"
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

extern int	g_status;

/* void	minishell_job(char *str, t_data *data, char **env2, char **tokens)
{
	ft_exit(str);
	if (str && *str != '\0' && ft_status(str))
	{
		add_history(str);
		g_status = general_function(str, &data, env2);
		if (tokens)
			free_d_array(tokens);
		if (!g_status)
			ft_exec(data, &env2);
		if (data)
			ft_lstclear1(&data);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	char	*str;
	char	**tokens;
	char	**env2;
	t_data	*data;

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
		if (str && *str != '\0')
			minishell_job(str, data, env2, tokens);
		else if (str)
			free(str);
	}
	free_d_array(env2);
	return (0);
}
 */

int	main(int argc, char *argv[], char **envp)
{
	extern int	g_status;
	char		*str;
	char		**tokens;
	char		**env2;
	t_data		*data;
	int			ret;

	ret = 0;
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
		if (str && *str != '\0')
		{
			ft_exit(str);
			if (str && *str != '\0' && ft_status(str))
			{
				add_history(str);
				ret = general_function(str, &data, env2);
				if (ret)
				g_status = ret;
				if (tokens)
					free_d_array(tokens);
				if (!ret)
					ft_exec(data, &env2);
				if (data)
					ft_lstclear1(&data);
			}
		}
		else if (str)
			free(str);
	}
	free_d_array(env2);
	return (0);
}
