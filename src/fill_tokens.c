/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 07:53:14 by caquinta          #+#    #+#             */
/*   Updated: 2022/11/05 14:12:13 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/utils2.h"
#include "../libft/libft.h"
#include "fill_tokens_utils.h"

void	fill_array1(char *str, char **tokens)
{
	int	x;
	int	index;

	index = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '|' || str[x] == '<' || str[x] == '>')
			index = check_char(str + x);
		else if (str[x] != ' ')
			index = count_word_index(str + x);
		if (str[x] != ' ')
		{
			*tokens = ft_substr(str + x, 0, (index));
			tokens[1] = ft_strdup(*tokens);
			ft_memset(tokens[1], '0', ft_strlen(tokens[1]));
			x += index - 1;
			tokens += 2;
		}
		x++;
	}
}

void	fill_map(char *quote, char *no, char **fill)
{
	int		check;
	char	*aux;
	char	c;
	int		x;

	x = 0;
	check = 0;
	aux = *fill;
	while (no[x])
	{
		check = check_assign(check, no[x], &quote, &c);
		if (check == 1)
		{
			while (*quote != c && no[x])
			{
				count_assign(&aux, &quote, &x, '1');
			}
			quote++;
			check = 0;
		}
		else if (check == 0)
			count_assign(&aux, &quote, &x, '1');
	}
}

void	fill_array2(char **tokens)
{
	int		x;
	char	*aux1;
	char	*aux2;
	char	*aux3;

	x = 0;
	while (tokens[x])
	{
		aux1 = erase_quotes(tokens[x]);
		if (ft_strncmp(tokens[x], aux1, __INT_MAX__) != 0)
		{
			aux2 = tokens[x];
			aux3 = tokens[x + 1];
			tokens[x] = ft_strdup(aux1);
			tokens[x + 1] = ft_strdup(aux1);
			fill_map(aux2, tokens[x], &tokens[x + 1]);
			free(aux3);
			free(aux2);
			free(aux1);
		}
		x += 2;
	}
}

char	**fill_tokens(char *str)
{
	char	**tokens;
	int		x;

	x = count_tokens(str);
	if (x == 0)
	{
		free (str);
		return (0);
	}
	tokens = (char **)ft_calloc(((x * 2) + 1), sizeof(char *));
	tokens[x * 2] = 0;
	if (!tokens)
		return (NULL);
	fill_array1(str, tokens);
	fill_array2(tokens);
	return (tokens);
}
