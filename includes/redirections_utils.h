/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:48:10 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/27 12:46:24 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_UTILS_H
# define REDIRECTIONS_UTILS_H
# include "utils.h"

t_data	*ft_lstnew2(void);
t_data	*ft_lstlast2(t_data *lst);
void	ft_lstadd_back2(t_data **lst, t_data *new);
t_data	*put_last_node(t_data *nodes);
int		check_pipe(char **tokens);

#endif