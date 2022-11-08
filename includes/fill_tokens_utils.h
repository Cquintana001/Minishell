/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:13:48 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/29 12:45:13 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_TOKENS_UTILS_H
# define FILL_TOKENS_UTILS_H

int		check_assign(int check, char a, char **quote, char *c);
void	count_assign(char **aux, char **quote, int *x, char a);
int		check_char(char *str);

#endif