/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:13:27 by amarzana          #+#    #+#             */
/*   Updated: 2022/11/04 08:03:38 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "double_red.h"
#include "fd_utils.h"
#include "signals.h"
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

extern int	g_status;

void	ft_get_fd(char *file, int mode, t_fd *fd)
{
	if (mode == 0)
	{
		ft_close(&fd->fdin, 0);
		fd->fdin = open(file, O_RDONLY);
	}
	else if (mode == 1)
	{
		ft_close(&fd->fdout, 0);
		fd->fdout = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (mode == 2)
	{
		ft_close(&fd->fdout, 0);
		fd->fdout = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else if (mode == 3)
		here_doc(file, fd);
}

void	ft_close(int *fd, int mode)
{
	if (*fd != -2)
		close(*fd);
	if (mode == 1)
		*fd = -2;
}

void	ft_init_fd(t_fd *fd)
{
	fd->in = dup(STDIN_FILENO);
	fd->out = dup(STDOUT_FILENO);
	fd->fdin = -2;
	fd->fdout = -2;
	fd->pipe[0] = -2;
	fd->pipe[1] = -2;
	fd->here_doc = 0;
	fd->key = NULL;
}

void	ft_close_all(t_fd *fd)
{
	ft_close(&fd->fdin, 0);
	ft_close(&fd->fdout, 0);
	ft_close(&fd->pipe[0], 0);
	ft_close(&fd->pipe[1], 0);
}

void	ft_reset_fd(t_fd *fd)
{
	dup2(STDIN_FILENO, fd->in);
	dup2(STDOUT_FILENO, fd->out);
}
