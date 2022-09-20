/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 10:47:48 by caquinta          #+#    #+#             */
/*   Updated: 2022/09/20 12:37:21 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

static char *str_len_malloc(char *str)
{
	int x;
	int space;
	char *array;
	space = 0;
	x = 0;
	while(str[x])
	{
		 
		if(str[x] == '|' || str[x] == '<' || str[x] == '>')
			space += 1;
		x++;
	}
	printf("longitud %d\n", x);
	x = x + (space * 2); // add two spaces for every '|', '<', '>';
	array = (char*)ft_calloc((x +1), sizeof(char));

	ft_memset(array, 'a', x);
	printf("HERE: %s\n", array);
	return(array);
}

static int second_char_exists(char *str, char a)
{
    char *array;

    array = ++str;
    while(*array)
    {
        if(*array == a)
            return(1);
        array++;
    }
    return(0);
}
static int find_len(char *str, char a)
{
	int x;

	x = 1;
	while(*(str +x) != a)
		x++;
	return(x+1);
}

void copy_until_char(char *ar, char *st, char a)
{
	int x;
	int i;

	i = 0;
	x = find_len(st, a);
	while(i < x)
	{
		*ar = *st;
		st ++;
		ar ++;
		i++;
	}
}
void add_space(char **array, char **str, char a)
{
	**array = ' ';
	(*array)++;
	**array = **str;
	(*array)++;
	(*str)++;
	if(a != '|' && a == **str)
	{	
		**array = **str;
		(*array)++;
		**array = ' ';
	}
	else
	{	
		(*str)--;
		**array = ' ';
	}
}
char *array(char *str)
{
	char *array;
	char *aux; 
	
	array =  str_len_malloc(str);
	aux = array;
	while(*str)
	{		 
		if(*str == '"' && second_char_exists(str, '"'))
			copy_until_char(array, str, *str);
		else if(*str == '\'' && second_char_exists(str, '\''))
			copy_until_char(array, str, *str);          
		if(*str == '|' || *str == '<' || *str == '>')
			add_space(&array, &str, *str);
		else	
			*array = *str;
		str++;
		array++;
	}
	*array = '\0';
	array = aux;
	aux = ft_substr(array, 0, ft_strlen(array));
	free(array);
	return(aux);
}