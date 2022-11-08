/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:07:30 by amarzana          #+#    #+#             */
/*   Updated: 2022/11/05 12:24:19 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtins.h"
#include "double_red.h"
#include "executor.h"
#include "fd_utils.h"
#include "signals.h"
#include "utils.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	ft_dup_work(t_fd *fd, int mode)
{
	if (fd->fdin == -1)
	{
		close(fd->fdin);
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		if (mode == 0)
			exit(1);
		return (0);
	}
	if (mode == 1)
		fd->fdin = -2;
	if (fd->fdin >= 0)
	{
		dup2(fd->fdin, STDIN_FILENO);
		close(fd->fdin);
	}
	if (fd->fdout >= 0)
	{
		dup2(fd->fdout, STDOUT_FILENO);
		close(fd->fdout);
	}
	return (1);
}

void	ft_dups(char **redir, t_fd *fd, t_data *node)
{
	int	i;

	i = 0;
	if (redir != NULL)
	{
		while (redir[i])
		{
			if (ft_strncmp(redir[i], "<", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 0, fd, node);
			else if (ft_strncmp(redir[i], ">", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 1, fd, node);
			else if (ft_strncmp(redir[i], ">>", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 2, fd, node);
			else if (ft_strncmp(redir[i], "<<", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 3, fd, node);
			i++;
		}
	}
}

void	ft_child(t_data *node, char **envp, t_fd *fd, int ret)
{
	ft_dup_work(fd, 0);
	if (node->cmd)
	{
		if (ft_is_builtin(node->cmd))
		{
			ft_call_builtin(node->cmd, &envp);
			ret = 0;
		}
		else
		{
			execve(node->path, node->cmd, envp);
		}
	}
	free(node->path);
	exit(ret);
}

void	ft_pipex(t_data *node, char **envp, t_fd *fd, int ret)
{
	pid_t	pid;

	ft_dups(node->redirection, fd, node);
	pipe(fd->pipe);
	pid = fork();
	if (pid < 0)
		perror("Error");
	if (pid == 0)
	{
		close(fd->pipe[0]);
		dup2(fd->pipe[1], STDOUT_FILENO);
		close(fd->pipe[1]);
		ft_child(node, envp, fd, ret);
	}
	else
	{
		close(fd->pipe[1]);
		dup2(fd->pipe[0], STDIN_FILENO);
		close(fd->pipe[0]);
		ft_close(&fd->fdin, 1);
		ft_close(&fd->fdout, 1);
		waitpid(pid, &ret, 0);
	}
}

int	ft_check_cmd(t_data *node, t_fd *fd, int *ret, int mode)
{
	if (node->path || ft_is_builtin(node->cmd))
		return (1);
	if (node->cmd)
	{
		if (ft_strncmp(node->cmd[0], "exit", ft_strlen(node->cmd[0])) == 0
			&& ft_strlen(node->cmd[0]) == 4)
			return (0);
		*ret = 32512;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->cmd[0], 2);
		ft_putendl_fd(" command not found", 2);
		ft_close(&fd->fdin, 1);
		ft_close(&fd->fdout, 1);
	}
	ft_dups(node->redirection, fd, node);
	if (mode == 1)
		close(STDIN_FILENO);
	ft_reset_fd(fd);
	return (0);
}
