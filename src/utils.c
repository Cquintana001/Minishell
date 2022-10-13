/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:36:24 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/13 07:45:05 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "lexer.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	second_char_exists(char *str, char a)
{
	str++;
	while (*str)
	{
		if (*str == a)
			return (1);
		str++;
	}
	return (0);
}

void	free_d_array(char **array)
{
	int	x;

	x = 0;
	while (array[x])
	{
		free(array[x]);
		x++;
	}
	free(array);
}

char	*find_path(char **envp)
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			return (ft_strchr(*envp, '/'));
		envp++;
	}
	return (0);
}

char	*check_if_command(char **envp, char *str)
{
	char	**path_list;
	char	*cmd;
	char	*full_cmd_path;
	int		x;

	x = 0;
	if (!str)
		return (0);
	cmd = ft_strjoin("/", str);
	path_list = ft_split(find_path(envp), ':');
	while (path_list[x])
	{
		full_cmd_path = ft_strjoin(path_list[x], cmd);
		if (access(full_cmd_path, F_OK) == 0)
		{
			free(cmd);
			free_d_array(path_list);
			return (full_cmd_path);
		}
		else if (access(str, F_OK) == 0)
		{
			free(cmd);
			free(full_cmd_path);
			free_d_array(path_list);
			return (str);
		}
		free(full_cmd_path);
		x++;
	}
	free(cmd);
	free_d_array(path_list);
	return (0);
}

int	file_exists(char *str)
{
	char	*file;

	file = ft_strjoin("./", str);
	return (access(file, F_OK));
}
