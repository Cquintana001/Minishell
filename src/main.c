/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:09:24 by caquinta          #+#    #+#             */
/*   Updated: 2022/11/07 14:42:57 by amarzana         ###   ########.fr       */
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

void	logic(char *str, char ***env2, t_data **data, char ***tokens)
{
	int	ret;

	ret = 0;
	ft_signals();
	str = get_str(*env2);
	if (str && *str != '\0')
	{
		ft_exit(str);
		if (str && *str != '\0' && ft_status(str))
		{
			add_history(str);
			ret = general_function(str, data, *env2);
			if (ret > 0)
				g_status = ret;
			if (!ret)
				ft_exec(*data, env2);
			if (*data)
				ft_lstclear1(data);
		}
		if (*tokens)
			free_d_array(*tokens);
	}
	else if (str)
		free(str);
}

int	main(int argc, char *argv[], char **envp)
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
	str = NULL;
	while (1)
	{
		logic(str, &env2, &data, &tokens);
	}
	free_d_array(env2);
	return (0);
}
