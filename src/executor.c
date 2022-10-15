/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:13:35 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/12 18:26:04 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "fd_stuff.h"
#include "utils.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "double_red.h"

//Makes required redirections before executing the command
static void	ft_dup_work(t_fd *fd)
{
	if (fd->fdin != -1)
	{
		dup2(fd->fdin, STDIN_FILENO);
		close (fd->fdin);
	}
	if (fd->fdout != -1)
	{
		dup2(fd->fdout, STDOUT_FILENO);
		close (fd->fdout);
	}
}

//Calls ft_get_fd for every redirection
static void	ft_dups(char **redir, t_fd *fd)
{
	int	i;

	i = 0;
	if (redir != NULL)
	{
		while (redir[i])
		{
			if (ft_strncmp(redir[i], "<", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 0, fd);
			else if (ft_strncmp(redir[i], ">", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 1, fd);
			else if (ft_strncmp(redir[i], ">>", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 2, fd);
			else if (ft_strncmp(redir[i], "<<", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 3, fd);
			i++;
		}
	}
}

//Makes the required dups and executes the command
static void	ft_child(t_data *node, char **envp, t_fd *fd)
{
	int fd1[2];
	pid_t pid;
	ft_dup_work(fd);
	if(fd->here_doc == 1)
	{
		 
		pipe(fd1);
		pid = fork();
		if(pid == 0)
		{	close(fd1[0]);
			dup2(fd1[1], STDOUT_FILENO);
			close(fd1[1]);
			double_redirection(fd->key);
		}
		else if(pid>0)
		{
			 
			close(fd1[1]);
			dup2(fd1[0], STDIN_FILENO);
			close(fd1[0]);
		}
	}
	
	if (execve(node->path, node->cmd, envp) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(node->cmd[0], 2);
		ft_putendl_fd("bash: command not found", 2);
		exit(0);
	}
}

//Creates a pipe and makes a fork.
//Calls ft_child in the child process
//Parent process closes fdin and fdout and waits for the child to end
static void	ft_pipex(t_data *node, char **envp, t_fd *fd)
{
	pid_t	pid;

	ft_dups(node->redirection, fd);
	pipe(fd->pipe);
	pid = fork();
	if (pid < 0)
		perror("Error");
	if (pid == 0)
	{
		close(fd->pipe[0]);
		dup2(fd->pipe[1], STDOUT_FILENO);
		close (fd->pipe[1]);
		ft_child(node, envp, fd);
	}
	else
	{
		close(fd->pipe[1]);
		dup2(fd->pipe[0], STDIN_FILENO);
		close (fd->pipe[0]);
		ft_close(fd->fdin);
		fd->fdin = -1;
		ft_close(fd->fdout);
		fd->fdout = -1;
		wait(NULL);
	}
}

//Returns the number of nodes of a linked list
static int	ft_count_nodes(t_data *node)
{
	int		node_nb;

	node_nb = 1;
	while (node->next)
	{
		node_nb++;
		node = node->next;
	}
	return (node_nb);
}

//Creates a t_fd structure and calls ft_pipex for every command
// except for the last or if there is only one.
//Closes all used fd and restores original STDIN and STDOUT
void	ft_exec(t_data *node, char **envp)
{
	int		node_nb;
	int		pid;
	t_fd	fd;

	ft_init_fd(&fd);
	node_nb = ft_count_nodes(node);
	pid = fork();
	if (pid < 0)
		perror("Error");
	if (pid == 0)
	{
		while (--node_nb)
		{
			ft_pipex(node, envp, &fd);
			node = node->next;
		}
		ft_dups(node->redirection, &fd);
		ft_child(node, envp, &fd);
	}
	else
	{
		wait(NULL);
		ft_close_all(&fd);
		ft_reset_fd(&fd);
	}
}
