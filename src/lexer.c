/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:09:24 by caquinta          #+#    #+#             */
/*   Updated: 2022/09/28 15:56:13 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <stdio.h>
#include "fill_tokens.h"
#include <fcntl.h>
#include "expansor2.h"

int second_char_exists(char *str, char a) // detecta si las comillas se cierran.
{
    char *array;

    array = ++str;
    while (*array)  
    {
        if (*array == a)
         {  
			return (1);
		 }
        array++;
    }
    return (0);
}

int count_char_index(char *str, char a) // cuenta el número de caracteres hasta que se cierran las comillas
{
    int x;

    str++;
    x = 0;
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

   	x = 0;
    while (*str)
    {

        if ((*str == '"' || *str == '\'') && second_char_exists(str, *str))
        {
            x += count_char_index(str, *str) + 1;
            str += count_char_index(str, *str) + 1;
 
        }
        else if (*str == '|' || *str == '<' || *str == '>' || *str == ' ')
            return (x);
        x++;
        str++;
        
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
         
        char **tokens;
        
        str = readline("minishell $ ");
        add_history(str);
        if (!str)
            exit(0);
        x = count_tokens(str);
        printf("número de tokens: %d\n", x);
        tokens = fill_tokens(str, x);
        
        while(*tokens)
        {
            //printf("variable: %s\n", *tokens);
            str = expansor(*tokens);  
            printf("variable: %s\n", str);
            free(str);
            tokens++;
        }
    }
    return 0;
}
