#include <stdlib.h>
#include <readline/readline.h> 
#include<readline/history.h>
#include "../libft/libft.h"
#include <stdio.h>
#include "lexer.h"
#include <fcntl.h>
#include "struct.h"
 
int second_char_exists(char *str, char a) // detecta si las comillas se cierran.
{
    
    str++;
        
        while (*str)  
        {
            if (*str == a)
             {  
                  printf("devuelvo 1");
	    		return (1);
	    	 }
            str++;
        }
    printf("devuelvo 0");
    return (0);
}

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
 
 