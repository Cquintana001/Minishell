/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 07:53:14 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/03 13:41:54 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/lexer.h"

int	check_char(char *str)
{
	if (*str == *(str + 1))
		return (2);
	return (1);
}

char	**fill_tokens(char *str)
{
	char	**tokens;
	int		index;
	char	**aux;
	int		x;

	x = count_tokens(str);
	index = 0;
	tokens = (char **)ft_calloc((x + 1), sizeof(char *));
	aux = tokens;
	if (!tokens)
		return (NULL);
	x = 0;
	while (str[x])
	{
		if (str[x] == '|' || str[x] == '<' || str[x] == '>')
		{
			index = check_char(str + x);
			*tokens = ft_substr(str + x, 0, index);
			x += index - 1;
			tokens++;
		}
		else if (str[x] != ' ')
		{
			index = count_word_index(str + x);
			*tokens = ft_substr(str + x, 0, (index));
			x += index - 1;
			tokens++;
		}
		x++;
	}
	return (aux);
}