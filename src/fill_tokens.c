/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 07:53:14 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/13 08:06:26 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/utils2.h"
#include "../libft/libft.h"

int	check_char(char *str)
{
	if (*str == *(str + 1))
		return (2);
	return (1);
}

void	fill_array1(char *str, char **tokens)
{
	int	x;
	int	index;

	index = 0;
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
}

void	fill_array2(char **tokens)
{
	char	*aux;
	int		x;

	x = 0;
	aux = NULL;
	while (tokens[x])
	{
		aux = tokens[x];
		tokens[x] = ft_strdup(erase_quotes(tokens[x]));
		free(aux);
		x++;
	}
}

char	**fill_tokens(char *str)
{
	char	**tokens;
	int		x;

	x = count_tokens(str);
	if (x == 0)
		return (0);
	tokens = (char **)ft_calloc((x + 1), sizeof(char *));
	tokens[x] = 0;
	if (!tokens)
		return (NULL);
	fill_array1(str, tokens);
	fill_array2(tokens);
	return (tokens);
}
