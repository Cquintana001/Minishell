/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:07:06 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/23 08:11:16 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "signals.h"
#include "fd_utils.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/wait.h>

char	*add_line_break(char *aux, char *str)
{
	char	*array;

	array = aux;
	aux = ft_strjoin(aux, "\n");
	free(array);
	array = aux;
	aux = ft_strjoin(aux, str);
	free(array);
	return (aux);
}

char	*double_redirection(char *key)
{
	char	*aux;
	char	*str;

	aux = 0;
	while (1)
	{
		ft_signals_in_cat();
		str = readline("heredoc> ");
		if (!str)
		{
			printf("bash: warning: here-document delimited by end-of-file (wanted `end')\n");
			printf("ft_exit con frees etc\n");
			break ;
		}
		if (!ft_strncmp(str, key, __INT_MAX__))
			break ;
		if (!aux)
			aux = ft_strdup(str);
		else
			aux = add_line_break(aux, str);
		free(str);
	}
	if (str)
		free(str);
	return (aux);
}

void	here_doc(char *key, t_fd *fd)
{
	int		fd1[2];
	pid_t	pid;
	char	*str;

	pipe(fd1);
	pid = fork();
	if (pid == 0)
	{
		close(fd1[0]);
		str = double_redirection(key);
		if (str)
			ft_putendl_fd(str, 1);
		close(fd1[1]);
		exit(0); //ft_exit
	}
	else
	{
		close(fd1[1]);
		wait(NULL);
		fd->fdin = dup(fd1[0]);
		close(fd1[0]);
	}
}
