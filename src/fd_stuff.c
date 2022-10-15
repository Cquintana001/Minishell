/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:13:27 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/12 17:42:12 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "fd_stuff.h"
#include <fcntl.h>

void	ft_close(int fd)
{
	if (fd != -1)
		close(fd);
}

void	ft_get_fd(char *file, int mode, t_fd *fd)
{
	if (mode == 0)
	{
		ft_close(fd->fdin);
		fd->fdin = open(file, O_RDONLY);
		if (fd->fdin < 0)
		{
			close(fd->fdin);
			ft_putstr_fd("Invalid or missing input file\n", 2);
			exit(0); //FT_EXIT CON FREES ETC
		}
	}
	else if (mode == 1)
	{
		ft_close(fd->fdout);
		fd->fdout = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (mode == 2)
	{
		ft_close(fd->fdout);
		fd->fdout = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else if (mode == 3)
	{
		fd->here_doc = 1;
		fd->key = file;

	}
}

void	ft_init_fd(t_fd *fd)
{
	fd->in = dup(STDIN_FILENO);
	fd->out = dup(STDOUT_FILENO);
	fd->fdin = -1;
	fd->fdout = -1;
	fd->pipe[0] = -1;
	fd->pipe[1] = -1;
	fd->here_doc = 0;
	fd->key = NULL;
}

void	ft_close_all(t_fd *fd)
{
	ft_close(fd->fdin);
	ft_close(fd->fdout);
	ft_close(fd->pipe[0]);
	ft_close(fd->pipe[1]);
}

void	ft_reset_fd(t_fd *fd)
{
	dup2(STDIN_FILENO, fd->in);
	dup2(STDOUT_FILENO, fd->out);
}
