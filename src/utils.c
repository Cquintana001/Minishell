/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:36:24 by caquinta          #+#    #+#             */
/*   Updated: 2022/11/04 08:02:01 by caquinta         ###   ########.fr       */
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
	while (array && array[x])
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

char	*check_str(char *f, char *str, char *cmd, char ***p)
{
	if (access(str, F_OK) == 0)
	{
		free(cmd);
		free(f);
		free_d_array(*p);
		return (ft_strdup(str));
	}
	else if (access(f, F_OK) == 0)
	{
		free(cmd);
		free_d_array(*p);
		return (f);
	}
	free(f);
	return (NULL);
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
	if (!access(str, F_OK))
		return (ft_strdup(str));
	cmd = ft_strjoin("/", str);
	path_list = ft_split(find_path(envp), ':');
	while (path_list && path_list[x])
	{
		full_cmd_path = ft_strjoin(path_list[x], cmd);
		full_cmd_path = check_str(full_cmd_path, str, cmd, &path_list);
		if (full_cmd_path != NULL)
			return (full_cmd_path);
		free(full_cmd_path);
		x++;
	}
	free(cmd);
	if (path_list)
		free_d_array(path_list);
	return (0);
}
