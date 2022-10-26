/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 07:51:39 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/26 10:43:25 by caquinta         ###   ########.fr       */
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

char  *ft_getenv2(char *s)
{
    if(getenv(s))
        return(getenv(s));
    else if(ft_strncmp(s, "?", ft_strlen(s))==0)
        return("0");
    else
        return(NULL);
    
}