#include <stdlib.h>
#include <readline/readline.h> 
#include<readline/history.h>
#include "../libft/libft.h"
#include <stdio.h>
#include "lexer.h"
#include "lexer1.h"
#include <fcntl.h>
#include "struct.h"
#include "fill_array.h"
#include "expansor.h"
 
void free_d_array(char **array)
{   
    int x;

    x = 0;
    while(array[x])
    {
        free(array[x]);
        x++;
    }
    free(array);
}
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
char *check_if_command(char **envp, char *str)
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
            return(full_cmd_path);
        free(full_cmd_path);
        x++;
    }
    free(cmd);
    free_d_array(path_list);       
    return(0);
}

int file_exists(char *str)
{
    char *file;

    file = ft_strjoin("./", str);
    return(access(file, F_OK));    
}
int main(int argc, char *argv[], char **envp)
{
    argc = 0;
    argv = NULL;
    t_data *args;
     
     while (1)
     {
        char *x ;
        char * str;
        char **split;

        str = readline("minishell $ ");
        add_history(str);
        if (!str)
            exit (0);
        x = array(str);
        printf("el array tokenizado es %s\n", x);       
        split = ft_split(x, ' ');
        split_expanded(split);
        args = set_array(split);
        free(x);
        char  *full_path = check_if_command(envp, split[0]);
        if(full_path)
             args->path = full_path;
        printf("full path es: %s\n", full_path);
        free(str); 
    }
}