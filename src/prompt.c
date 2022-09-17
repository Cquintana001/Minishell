#include <stdlib.h>
#include <readline/readline.h>
#include <stdio.h>
#include "../libft/libft.h"
 #include <stdio.h>
#include "lexer.h"
#include "lexer1.h"
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
    char *x ;
        char * str = readline("Quintashell $ ");
        /* if(!(*str))
            continue; */
        x = array(str);
        printf("el array original es %s\n", str);
        printf("el array parseado es %s\n", x);
        free(str);
        /* while(array[x])
        {
            printf("%s\n", array[x]);
            x++;;
        }
        free(array); */
    }
} 