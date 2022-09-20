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
    int x;

    x = 0;
    cmd = ft_strjoin("/", str);
    path_list = ft_split(find_path(envp), ':');
    while(path_list[x])
    {
        full_cmd_path = ft_strjoin(path_list[x], cmd);
         
        if(access(full_cmd_path, F_OK) == 0)
            return(1);
        free(full_cmd_path);
        x++;
    }
    free(cmd);
    x = 0;
    while(path_list[x])
    {
        free(path_list[x]);
        x++;
    }
    free(path_list); 
         
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
        if (!str)
            exit (0);
        x = array(str);
         
        split = ft_split(x, ' ');
        free(x);
        int ok = check_if_command(envp, split[0]);
        if(ok)
            printf("es un comando\n");
        else
            printf("no es un comando\n");
         
        free(str); 
    }
}