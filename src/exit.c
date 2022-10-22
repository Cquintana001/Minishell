/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 07:51:39 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/22 08:53:05 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "general_function.h"

int ft_exit(char *str)
{
   if(ft_strncmp(str, "exit", 4)==0)
    {
        free(str);    
        exit(0);
    }

    return(0);   
}