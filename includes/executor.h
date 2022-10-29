/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:18:45 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/28 11:45:05 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "utils.h"
# include "fd_utils.h"

//executor.c

//Creates a t_fd structure and calls ft_pipex for every command
// except for the last or if there is only one.
//Closes all used fd and restores original STDIN and STDOUT
int		ft_exec(t_data *node, char ***envp);

//executor2.c

int		ft_check_cmd(t_data *node, t_fd *fd, int *ret, int mode);

//Creates a pipe and makes a fork.
//Calls ft_child in the child process
//Parent process closes fdin and fdout and waits for the child to end
void	ft_pipex(t_data *node, char **envp, t_fd *fd, int ret);

//Makes the required dups and executes the command
void	ft_child(t_data *node, char **envp, t_fd *fd, int ret);

//Calls ft_get_fd for every redirection
void	ft_dups(char **redir, t_fd *fd);

//Makes required redirections before executing the command
int		ft_dup_work(t_fd *fd, int mode);

//exec_utils.c

void	ft_call_builtin(char **cmd, char ***envp);

//Checks if the given variable is full alphanumeric
int		ft_check_var(char *var, char *cmd);

//Checks if given command is ft_builtin
//Returns	1 if cmd is "pwd", "echo" or "env"
//and		2 if cmd is "export", "unset" or "chdir"
int		ft_is_builtin(char **cmd);

//Returns the number of nodes of a linked list
int		ft_count_nodes(t_data *node);

//Returns the variable without = and the value
char	*ft_subst_var(char *var);


#endif