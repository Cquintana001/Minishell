/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:35:45 by caquinta          #+#    #+#             */
/*   Updated: 2022/11/05 11:46:40 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_data
{
	char			**cmd;
	char			**redirection;
	char			*path;
	int				input;
	int				output;
	char			**tokens;
	int				here_doc;
	struct s_data	*next;

}			t_data;

void		free_d_array(char **array);
char		*find_path(char **envp);
char		*check_if_command(char **envp, char *str);
int			file_exists(char *str);
int			second_char_exists(char *str, char a);
#endif