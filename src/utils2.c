/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 09:05:01 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/03 10:24:59 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "lexer.h"

 
int count_index(char *str)
 {
	int x;
	 int i;
	int q;
	char *aux;
	q = 0;
	x = 0;
	 i=0;
	while(str[x])
	{
		 if(str[x]== '"' || str[x] == '\'')
		 {	
			aux = (str +x);
			q = count_char_index(aux, str[x]);
		 	i += q;
			x +=q +1 ;
		}
		else
		{
			x++;
			i++;
		}			 
	}	
	 
	return(i );	
 }
void fill_array(char *source, char *dest)
{
	int x;
	int check;

	check = 0;
	while(*source)
	 {
		x = 1;
		if((*source == '\'' || *source == '"') )
		{
			if(check == 0)
			{	
				x = count_char_index(source, *source) -1;
				source++;
				check = 1;
			}
			else
			{	
				source++;
				check = 0;
				x = 0;
			}
		}		 
		while(x)
		{
			*dest = *source;
			x--;
			source++;
			dest++;
		}
		
	}
	
}
 char *erase_quotes(char *str)
 {
	int x;
	char * array;
	x = count_index(str);
	  
	if(x == 0 || x == -1 )
		return(str);
	else  
	{
		printf("x es: %d\n",x);
		array = (char*)ft_calloc(x, sizeof(char));
		array[x-1] = '\0';
		fill_array(str, array);
	}	
	return(array);	
 }