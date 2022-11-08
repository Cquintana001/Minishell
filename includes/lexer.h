/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:45:47 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/29 12:46:05 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

int		count_word_index(char *str);
int		count_char_index(char *str, char a);
int		count_tokens(char *str);
char	*get_str(char **env);

#endif