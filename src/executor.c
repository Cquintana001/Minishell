/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:13:35 by amarzana          #+#    #+#             */
/*   Updated: 2022/11/04 08:26:03 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtins.h"
#include "double_red.h"
#include "executor.h"
#include "fd_utils.h"
#include "signals.h"
#include "utils.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern int	g_status;

static int	ft_single_builtin(t_data *node, t_fd fd, char ***envp, int node_nb)
{
	if (node_nb == 1 && ft_is_builtin(node->cmd) == 2)
	{
		ft_dups(node->redirection, &fd);
		ft_close(&fd.fdin, 0);
		if (ft_dup_work(&fd, 1))
			ft_call_builtin(node->cmd, envp);
		return (0);
	}
	return (1);
}

static int	ft_exec_loop(int node_nb, t_fd *fd, char ***envp, t_data *node)
{
	int	ret;
	int	pid;

	ret = 0;
	ft_signals_in_cat();
	pid = fork();
	if (pid == 0)
	{
		while (--node_nb)
		{
			if (ft_check_cmd(node, fd, &ret, 1))
				ft_pipex(node, *envp, fd, ret);
			node = node->next;
		}
		if (ft_check_cmd(node, fd, &ret, 0))
		{
			ft_dups(node->redirection, fd);
			ft_child(node, *envp, fd, ret);
		}
		else
			exit(127);
	}
	else
		waitpid(pid, &ret, 0);
	return (ret);
}

void	ft_exec(t_data *node, char ***envp)
{
	int		node_nb;
	t_fd	fd;

	ft_init_fd(&fd);
	node_nb = ft_count_nodes(node);
	if (ft_single_builtin(node, fd, envp, node_nb))
		g_status = ft_exec_loop(node_nb, &fd, envp, node);
	ft_close_all(&fd);
	ft_reset_fd(&fd);
}
