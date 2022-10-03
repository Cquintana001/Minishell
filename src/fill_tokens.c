/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 07:53:14 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/03 09:44:04 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "lexer.h"

int	check_char(char *str)
{
	if (*str == *(str + 1))
		return (2);
	return (1);
}

char	**fill_tokens(char *str, int x)
{
	char	**tokens;
	int		index;
	char	**aux;

	index = 0;
	tokens = (char **)ft_calloc((x + 1), sizeof(char *));
	aux = tokens;
	if (!tokens)
		return (NULL);
	while (*str)
	{
		if (*str == '|' || *str == '<' || *str == '>')
		{
			index = check_char(str);
			*tokens = ft_substr(str, 0, index);
			str += index - 1;
			tokens++;
		}
		else if (*str != ' ')
		{
			index = count_word_index(str);
			*tokens = ft_substr(str, 0, (index));
			str += index - 1;
			tokens++;
		}
		str++;
	}
	return (aux);
}