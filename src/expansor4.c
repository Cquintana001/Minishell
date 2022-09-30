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
	if(*str == '?' )
		return(1);
	while(*str && ( (*str >= '0' && *str <='9') || (*str >='A' && *str <= 'Z')\
		|| (*str >= 'a' && *str <='z' ) || *str =='_'))
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
	char *anadido;
	
	resultado = "";
	string = "";
	anadido = "";
	aux = str;
	while(*str)
	{		
		resultado = expansion(str); 
		if(*str == '$' &&  resultado)
		{
			if(!str[1])
				return(ft_strdup("$"));
			string = ft_substr(aux, 0, (str -aux));
			variable = getenv( resultado);
			free(resultado);
			if(variable == NULL)
				variable ="";
			anadido = ft_strjoin(string, variable);
			free(string);
			resultado = ft_strjoin(resultado, anadido);
			free(anadido);
			str += ft_strlen(resultado) + 1;
			free(resultado);
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