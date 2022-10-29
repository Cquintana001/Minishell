/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:13:35 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/29 08:09:07 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "double_red.h"
#include "fd_utils.h"
#include "utils.h"
#include "executor.h"
#include "builtins.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

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

int	ft_exec(t_data *node, char ***envp)
{
	int		node_nb;
	int		pid;
	t_fd	fd;
	int		ret;

	ret = 0;
	ft_init_fd(&fd);
	node_nb = ft_count_nodes(node);
	signal(SIGINT, SIG_IGN);
	if (ft_single_builtin(node, fd, envp, node_nb))
	{
		pid = fork();
		if (pid < 0)
			perror("Error");
		if (pid == 0)
		{
			while (--node_nb)
			{
				if (ft_check_cmd(node, &fd, &ret, 1))
					ft_pipex(node, *envp, &fd, ret);
				node = node->next;
			}
			if (ft_check_cmd(node, &fd, &ret, 0))
			{
				ft_dups(node->redirection, &fd);
				ft_child(node, *envp, &fd, ret);
			}
			else
				exit(127);
		}
		else
			waitpid(pid, &ret, 0);
	}
	ft_close_all(&fd);
	ft_reset_fd(&fd);
	return (ret);
}
