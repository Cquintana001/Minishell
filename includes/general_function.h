/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_function.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:16:36 by caquinta          #+#    #+#             */
/*   Updated: 2022/11/05 14:18:29 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_FUNCTION_H
# define GENERAL_FUNCTION_H
# include "utils.h"

int		general_function(char *str, t_data **data, char **env2);
void	ft_lstclear1(t_data **lst);

#endif