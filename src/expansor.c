/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 09:50:25 by caquinta          #+#    #+#             */
/*   Updated: 2022/09/26 08:54:24 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

char *check_dollar(char *str)
{
    char *aux = str;

   while(*str)
   {
        if(*str == '$' && *(++str))
        {    

            return(aux);
        }
        str++;
   } 
    return(0);
}
char  **detect_expansion(char **split)
{
	char **aux = split;
	while(*aux)
	{
		printf("split: %s\n", *aux);
		aux++;
	}
    while(*split)
    {
        if(*split[0]!= '\'' && check_dollar(*split) != 0)
         {   
			printf("string a exp: %s\n",*split);
			return(split); //devuelvo el puntero que apunta al string a expandir.
		 }
        split++;
    }
    return(0);

}
int len(char *str)
{
	int x;

	x = 0;
	while(*str != '$')
		str++;
	str++;
	while(*str && ( (*str > 47 && *str <59) || (*str > 64 && *str <91) || (*str > 96 && *str <123)))
	{
		str++;
		x++;		
	}
	return(x);
}

void fill_malloc(char *array, char *str)
{
	while (*str != '$')
	{
		str++;
	}
	str++;
	while(*array)
	{
	 
		*array = *str;
		str++;
		array++;
	}
}

char *expansion(char *str)
{
	char *array;
	array = (char*)malloc((len(str) +1) * sizeof(char));
	printf("longitud variable es: %d\n", len(str));
	ft_memset(array, 'a', len(str));
	fill_malloc(array, str);
	printf("array es: %s\n", array);
	 	
	return(array);	
}
void split_expanded(char **split)
{
	char **str;
	char *exp;
	 
	if(detect_expansion(split)!= 0)
	{	
		str = detect_expansion(split); //posicion del split a expandir;
		printf("posicion: %p\n", str);
		exp = expansion(*str); // nombre de la variable a expandir;
		printf("variable a expandir: %s\n", exp);
	if(getenv(exp))
		printf("variable expandida: %s\n", getenv(exp) );
	printf("string a expandir: %s\n", *str);
	}
 
	 
}