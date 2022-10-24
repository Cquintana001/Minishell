/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:13:36 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/23 09:55:31 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//Prints the path of the actual working directory
void	ft_pwd(void);

//Changes current working directoy, updating PWD and OLDPWD
void	ft_chdir(char *dir, char ***env);

//Adds/replaces variable in environment
//Hay que meter '=' después de var porque si no puede confundir
//variables que empiecen igual.
void	ft_export(char **cmd, char ***env);
void	ft_export_job(char *var, char *value, char ***env);

//Prints the env
void	ft_env(char **env, int mode);

//Removes variable from environment
//Si no coincide no hace nada
//Hay que meter '=' después de var porque si no puede confundir
//variables que empiecen igual.
void	ft_unset(char *var, char ***env);

//Prints arguments separated with a space followed by a new line
//Flag "-n" - Do not output a trailing newline.
void	ft_echo(char **cmd, char **env);

char	*ft_subst_var(char *var);
#endif