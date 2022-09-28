/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:00:41 by caquinta          #+#    #+#             */
/*   Updated: 2022/09/28 16:11:51 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

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
		printf("where: %c\n", *array);
		*array = *str;
		str++;
		array++;
	}
}

char *expansion(char *str)
{
	char *array;
	array = (char*)malloc((len(str) +1) * sizeof(char));
 
	ft_memset(array, 'a', len(str));
	array[len(str)] = 0;
	fill_malloc(array, str);
 
	 	
	return(array);	
}

char *expansor(char *str)
{
	char *aux;
	char *string;
	char *resultado;
	char *variable;
	char *añadido;
	
	aux = str;
	printf("str: %s\n", str);
	while(*str)
	{		 
		if(*str == '$' && expansion(str) )
		{
			string = ft_substr(aux, 0, (str -aux));
			variable = getenv( expansion(str));
			printf("variable: %s\n", variable);
			añadido = ft_strjoin(string, variable);
			printf("añadido: %s\n", añadido);
			resultado = ft_strjoin(resultado, añadido);
			str += ft_strlen(expansion(str)) +1 ;
			aux = str;
			printf("char: %c\n", *str);		 
		}
		str++;
	}
	string = ft_substr(aux, 0, (str -aux));
	resultado = ft_strjoin(resultado, string); 
	printf("resultado2: %s\n", resultado);	
	return(resultado);
}