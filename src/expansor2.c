/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:00:41 by caquinta          #+#    #+#             */
/*   Updated: 2022/09/29 13:53:01 by caquinta         ###   ########.fr       */
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
	if(*str == '?' || *str == '_')
		return(1);
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
	//printf("char: %c\n", *str);
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
	
	resultado = "";
	string = "";
	añadido = "";
	aux = str;
	while(*str)
	{		 
		if(*str == '$' &&  expansion(str))
		{
			if(!str[1])
				return(ft_strdup("$"));
			string = ft_substr(aux, 0, (str -aux));
			variable = getenv( expansion(str));
			if(variable == NULL)
				variable ="";
			añadido = ft_strjoin(string, variable);
			free(string);
			resultado = ft_strjoin(resultado, añadido);
			free(añadido);
			str += ft_strlen(expansion(str)) + 1;
			aux = str;	 
		}
		if(*str && *str != '$')
			str++;
	}
	string = ft_substr(aux, 0, (str -aux));
	resultado = ft_strjoin(resultado, string);
	free(string);
	return(resultado);
}