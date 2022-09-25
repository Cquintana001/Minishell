/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 09:50:25 by caquinta          #+#    #+#             */
/*   Updated: 2022/09/25 14:01:32 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

/* char *check_dollar(char *str)
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
char  *detect_expansion(char **split)
{
    while(*split)
    {
        if(*split[0]!= '\'' && check_dollar(*split) != 0)
            return(*split);
        split++;
    }
    return(0);

} */
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
	 	
	return(getenv(array));	
}