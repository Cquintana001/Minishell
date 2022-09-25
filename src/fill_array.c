/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:56:55 by caquinta          #+#    #+#             */
/*   Updated: 2022/09/24 12:11:35 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stdlib.h>
#include "lexer1.h"

t_data *set_array(char **str)
{
	int x;
	t_data *array;
	x = 0;
	while(*str)
	{
		if(str[0][0] == '|')
			x++;
		str++;		
	}
	array = (t_data*)malloc(sizeof(t_data) * (x+1));
	
		return(array);
}
/* void fill_data(t_data *data, char  **str)
{
	int x;

	x = 0;
	while(*str)
	{
		 
			 
		
		
	}

}
t_data *fill_array(char **str)
{

	t_data *array;

	array = set_array(str);
	
} */