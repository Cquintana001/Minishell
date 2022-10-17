/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 07:53:14 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/17 11:24:46 by caquinta         ###   ########.fr       */
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
	char **aux;

	aux = tokens;
	index = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '|' || str[x] == '<' || str[x] == '>')
		{
			index = check_char(str + x);
			*tokens = ft_substr(str + x, 0, index);
			tokens[1] = ft_strdup(*tokens);
			ft_memset(tokens[1], '0', ft_strlen(tokens[1]));
			x += index - 1;
			tokens+=2;
		}
		else if (str[x] != ' ')
		{
			index = count_word_index(str + x);
			*tokens = ft_substr(str + x, 0, (index));
			tokens[1] = ft_strdup(*tokens);
			ft_memset(tokens[1], '0', ft_strlen(tokens[1]));
			x += index - 1;
			tokens+=2;
		}
		x++;
	}
	x = 0;
	tokens = aux;
	while(aux[x])
	{
		printf("token %d %s\n",x, aux[x]);
		x++;
		
	}
}
void fill_map(char *quote, char*no, char **fill)
{
	int check;
	char *aux;
	char c;
	int x;

	x = 0;
	check = 0;
	aux = *fill;
	
	while(no[x])
	{
		printf("entra\n");
		if(no[x] != *quote && check == 0)
		{	check = 1;
			c = *quote;
			quote++;
		}
		else if (no[x] != *quote && check == 1)
		{	
			check = 0;
			quote++;
		}
		if(check ==1)
		{
			 
			while(*quote != c && no[x])
			{
				*aux= '1';
				quote++;
				aux++;
				x++;
			}
			 
			quote++;
			check = 0;
		}
		else if(check == 0)
		{
			*aux = '0';
			quote++;
			x++;
			aux++;
		}
		 
		/* if(*quote)
		{
		if(check == 0)
		{	
			*aux = '0';
			 
		}
		else if(check == 1)
		{	*aux= '1';
			 
		}
		quote++;
		no++;
		aux++;
		} */
 
	}

	
}
void	fill_array2(char **tokens)
{
	int		x;
	char	*aux1;
	char	*aux2;
	char *aux3;
	 
	x = 0;
	while (tokens[x])
	{
 
		aux1 = erase_quotes(tokens[x]);
		if(ft_strncmp(tokens[x], aux1, __INT_MAX__)!= 0)
		{	
			aux2 = tokens[x];
			aux3 = tokens[x+1];
			tokens[x] = ft_strdup(aux1);
			tokens[x+1] = ft_strdup(aux1); //LIBERAR TOKENS [X+1];
			fill_map(aux2, tokens[x], &tokens[x +1]);
			free(aux3)	;
			free(aux2);
			free(aux1);
			 
		}
		 
		x+=2;
	}
	x = 0;
	while(tokens[x])
	{
		printf("token %d %s\n",x, tokens[x]);
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
	tokens = (char **)ft_calloc(((x * 2) + 1), sizeof(char *));
	tokens[x*2] = 0;
	if (!tokens)
		return (NULL);
	fill_array1(str, tokens);
	fill_array2(tokens);
	return (tokens);
}
