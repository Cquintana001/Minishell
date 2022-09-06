#include <stdlib.h>
#include <readline/readline.h>
#include <stdio.h>
#include "../libft/libft.h"
 #include <stdio.h>

/* int main(int argc, char *argv[], char *envp[])
{
   printf("argc= %d\n", argc);
    printf("argv= %s\n", argv[0]);
   
    while(*envp)
        printf("%s\n",*envp++);
} */
 int main(void)
{
    while (1)
    {
        char * str = readline("Myshell $ ");
        ft_split(str, ' ');
        while(str)
        {
            printf("%s\n", str);
            str++;
        }
        free(str);
    }
} 