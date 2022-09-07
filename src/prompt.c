#include <stdlib.h>
#include <readline/readline.h>
#include <stdio.h>
#include "../libft/libft.h"
 #include <stdio.h>
#include "lexer.h"

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
    int x = 0;
        char * str = readline("Myshell $ ");
        /* if(!(*str))
            continue; */
        x = count_words(str);
        printf("el número de palabras es %d\n", x);
        free(str);
        /* while(array[x])
        {
            printf("%s\n", array[x]);
            x++;;
        }
        free(array); */
    }
} 