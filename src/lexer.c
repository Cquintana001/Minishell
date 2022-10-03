/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:09:24 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/03 07:47:55 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <stdio.h>
#include "fill_tokens.h"
#include <fcntl.h>
#include "expansor.h"
#include "utils.h"
#include "utils2.h"

int count_char_index(char *str, char a) // cuenta el número de caracteres hasta que se cierran las comillas
{
    int x;

    str++;
    x = 1;
    while (*str)
    {
        if (*str == a)
            return (x);
        str++;
        x++;
    }
    return (-1);
}
int count_word_index(char *str) // devuelve la posición final de la palabra
{
    int x;
    int i;
    i = 0;
   	x = 0;
    while (*str)
    {
        if ((*str == '"' || *str == '\'') )
        {
           if(!second_char_exists(str, *str)) 
            {
                printf("error\n");
                return(-1);
            }  
            i =   count_char_index(str, *str);
            x += i +1;
            str += i +1; 
        }
        else if (*str == '|' || *str == '<' || *str == '>' || *str == ' ')
            return (x);
        else
        {x++;
        str++;
        }      
    }
    return (x);
}
int count_tokens(char *str)
{
    int num_token;
    int index;

    index = 0;
    num_token = 0;
    while (*str)
    {
        if (*str == '|' || *str == '<' || *str == '>')
            num_token++;
        else if (*str != ' ')
        {
            index = count_word_index(str);
            if(index<0)
                return(0);
            str += index  -1;
            num_token++;
        }
        str++;
    }
    return (num_token);
}
int main()
{

    char *str;
     while (1)
    { 
        int x;
         char *aux;
        char **tokens;
       char *i;
        
        str = readline("minishell $ ");
        add_history(str);
        if (!str)
            exit(0);
        aux  = expansor(str);
        x = count_tokens(aux);
        if(!x)
        {
            printf("error\n");
            return(0);
        }
        tokens = fill_tokens(aux, x);
        free(aux);
        x = 0;
        
        while(tokens[x])
        {    
            printf("el token es %s\n", tokens[x]);   
           i = erase_quotes(tokens[x]);
          printf("el array es %s\n", i);
              
            
            
            x++;
        }
        /* x = 0;
        while(tokens[x])
        {       
           
          printf("token %d es: %s\n",x, tokens[x]);
             
            
            x++;
        } */
        free_d_array(tokens);
        //free(str);
     } 
    return 0;
}
