/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:18:45 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/21 16:23:04 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "utils.h"

//Creates a t_fd structure and calls ft_pipex for every command
// except for the last or if there is only one.
//Closes all used fd and restores original STDIN and STDOUT
void	ft_exec(t_data *node, char ***envp);

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