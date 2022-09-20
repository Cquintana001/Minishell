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
                return(ft_strchr(*envp, '/'));
            envp++;
        }
    return(0);
}
int check_if_command(char **envp, char *str)
{
    char **path_list;
    char *cmd;
    char *full_cmd_path;

    cmd = ft_strjoin("/", str);
    path_list = ft_split(find_path(envp), ':');
    while(*path_list)
    {
        full_cmd_path = ft_strjoin(*path_list, cmd);
        if(access(full_cmd_path, F_OK) == 0)
            return(0);
        path_list++;
    }
    return(1);

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
/*         char *path = ft_strjoin("/bin/", split[0]);
        int ok = access(path, F_OK);
        path = find_path(envp);
        char **array = ft_split(path, ':'); */
        int ok = check_if_command(envp, split[0]);
        printf("el archivo da %d\n", ok);
        /* while(*array)
        {
        printf("el path es: %s\n", *array);
        array++;
        } */
         
                
         
        /* while(*split)
        { 
            printf("el array spliteado es %s\n", *split);
            split++;
        } */
        free(str); 
    }
}