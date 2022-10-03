/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 07:53:14 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/03 15:17:39 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/lexer.h"
#include "../includes/utils2.h"

int	check_char(char *str)
{
	if (*str == *(str + 1))
		return (2);
	return (1);
}

void fill_array1(char *str, char **tokens)
{	
	int x;
	int index;

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
void fill_array2(char **tokens)
{
	char *aux;
	int x;

	x = 0;
	aux = NULL;
	while(tokens[x])
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
	int		index;
	char	**aux;
	int		x;

	x = count_tokens(str);
	index = 0;
	tokens = (char **)ft_calloc((x + 1), sizeof(char *));
	tokens[x] = 0;
	aux = tokens;
	if (!tokens)
		return (NULL);	 
	fill_array1(str, tokens);
	fill_array2(tokens);
	return (tokens);
}