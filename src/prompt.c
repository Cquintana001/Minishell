#include <stdlib.h>
#include <readline/readline.h> 
#include<readline/history.h>
#include "../libft/libft.h"
#include <stdio.h>
#include "lexer.h"
#include "lexer1.h"

char *find_path(char **envp)
{
  
    while(*envp)
        {
            if(ft_strnstr(*envp, "PATH=", 5))
                return(*envp);
            envp++;
        }
    return(0);
}

int main(int argc, char *argv[], char **envp)
{
    argc = 0;
    argv = NULL;
    while (1)
    {
        char *x ;
        char * str = readline("Quintashell $ ");
        add_history(str);
        char **split;
        x = array(str);
        split = ft_split(x, ' ');
        char *path = ft_strjoin("/bin/", split[0]);
        int ok = access(path, F_OK);
        path = ft_strchr(find_path(envp), '/');

        char **array = ft_split(path, ':');
        printf("el archivo da %d\n", ok);
        while(*array)
        {
        printf("el path es: %s\n", *array);
        array++;
        }
         
                
         
        /* while(*split)
        { 
            printf("el array spliteado es %s\n", *split);
            split++;
        } */
        free(str); 
    }
}