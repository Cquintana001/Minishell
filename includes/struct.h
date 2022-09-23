/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:53:15 by caquinta          #+#    #+#             */
/*   Updated: 2022/09/23 10:54:00 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
 

typedef struct s_data{	
	char *path; 
	char *cmd;
	char *flags;
	int fd[2];
	int infile;
	int outfile;
	
}	t_data;

 

#endif