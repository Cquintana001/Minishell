/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:15:34 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/23 09:30:15 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_UTILS_H
# define FD_UTILS_H

typedef struct s_fd
{
	int	in;
	int	out;
	int	fdin;
	int	fdout;
	int	pipe[2];
	int here_doc;
	char *key;
}			t_fd;

//Closes an fd only if it is used
void	ft_close(int fd);

//Closes all the fds of a t_fd structure
void	ft_close_all(t_fd *fd);

//Opens a file and saves its fd into the t_fd structure
void	ft_get_fd(char *file, int mode, t_fd *fd);

//Inits the values of a t_fd structure
void	ft_init_fd(t_fd *redir);

//Makes a dup2 restoring original STDIN and STDOUT
void	ft_reset_fd(t_fd *redir);

void	here_doc(char *key, t_fd *fd);

#endif