/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 10:47:48 by caquinta          #+#    #+#             */
/*   Updated: 2022/09/17 13:15:44 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>


/* static char *space_trim(char *str)
{
    
    while(*str == ' ' && *str)
        str++;
    return(str);
} */

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
	return(x);
}

char *array(char *str)
{
	int x;
	int i;
	char *array = 0;
	char *aux = array;
	printf("entra");
	while(*str)
	{
		i = 0;
		if(*str == '"' && second_char_exists(str, '"'))
           {
             x = find_len(str, '"');
			 printf("numero caracteeres es %d\n", x);
			 while(i < x)
			 {
				printf("entra1");
				*array = *str;
				str ++;
				array ++;
				i++;
			 }
           }
		else if(*str == '\'' && second_char_exists(str, '\''))
           {
             x = find_len(str, '\'');
			 while(i<x)
			 {
				*array = *str;
				str ++;
				array ++;
				i++;
			 }
           }
		else if(*str == '|' || *str == '<' || *str == '>')
        {
			*array = ' ';
            *(++array) = *str;
            *(++array) = ' ';
			str++;
        }
		else
		{	
			*array = *str;
			str++;
			array++;
		}
 
	}
	array = 0;
	return(aux);
}