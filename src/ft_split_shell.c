/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 09:08:35 by caquinta          #+#    #+#             */
/*   Updated: 2022/09/26 12:26:08 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer1.h"
#include <stdio.h>

static char *count_chr(char *str, int *x)
{
	char a;
	a = *str;
	printf("char es %c\n", a);
 
	str++;
	(*x)++;
	while(*str != a)
				str++;	
	return(str);
}
char *malloc_char(char *array, char a)
{
	int x;
	char *str;

	x = find_len(array, a);
	str = (char *)malloc(sizeof(char)*x);
	while(x)
	{
		*str = *array;
		x--;
	}
	return(str);	
}
char *malloc_char2(char *array)
{
	int x;
	char *str;

	
	x = 0;
	while(*array != ' ' &&*array != '\'' && *array != '"' )
		x++;
	str = (char *)malloc(sizeof(char)*(x +1));
	while(x)
	{
		*str = *array;
		x--;
	}
	return(str);	
}
int ft_split_shell(char *str)
{
	int x;
	int check;

	check = 0;
	x = 0;
	while(*str)
	{ 
		if(*str == ' ')
			check = 0;
		else if(*str == '\'' && second_char_exists(str, '\''))
			str = count_chr(str, &x);	 
		else if(*str == '"' && second_char_exists(str, '"'))
			str = count_chr(str, &x);	 
		else if(check == 0)
		{ 	
			check = 1;	 
			x++;
		}
		str++;			
	}
	return(x);
}
char *fill_tokens(char **str, char *array)
{
	while(*array)
	{
		if(*array == ' ')
			array++;
		else if(*array == '\'' && second_char_exists(array, '\''))
			*str = malloc_char(array, *array); 
		else if(*str == '"' && second_char_exists(array, '"'))
			*str = malloc_char(array, *array);	 
		else  
		{ 	
			*str = malloc_char2(array);
		}
	 	str++;
		
	}

	
}
char **return_tokens(char *str)
{
	int x;
	char **tokens;
	x = ft_split_shell(str);
	tokens = (char**) malloc(sizeof(char*) * (x +1));
	fill_tokens(tokens, str);
	 
}