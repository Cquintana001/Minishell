/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:48:10 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/07 10:55:01 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_UTILS_H
# define REDIRECTIONS_UTILS_H
# include "utils.h"

t_data	*ft_lstnew2(void *content);
t_data	*ft_lstlast2(t_data *lst);
void	ft_lstadd_back2(t_data **lst, t_data *new);
t_data	*put_last_node(t_data *nodes);
void	check_pipe(char **tokens);

#endif