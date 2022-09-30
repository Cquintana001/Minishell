
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

int len(char *str)
{
	int x;

	x = 0;
	while(*str != '$')
		str++;
	str++;
	if(*str == '?' || *str == '$' )
		return(1);
	while(*str && ( (*str >= '0' && *str <='9') || (*str >='A' && *str <= 'Z')\
		|| (*str >= 'a' && *str <='z' ) || *str =='_'))
	{
		str++;
		x++;		
	}
 
	return(x);
}

char *dollar_variable(char *str, int x )
{
    char *array;
     int l;

     l = len(str);
	array = (char*)calloc((l  +1), sizeof(char));
    ft_memset(array, 'a', l );
	array[l] = 0;
    x++;
    l = 0;
	while(array[l])
    {
        array[l] = str[x];
    
        l++;
        x++;
    } 	
    printf("array: %s\n", array);
	return(array);	
}

char *expansor(char *str)
{
    int x;
    char *var;
    char *first_part;
    char *second_part;
    x = 0;
    while(str[x])
    {
        if(str[x] == '$')
        {
           
            var = dollar_variable(str,  x);
            first_part = ft_substr(str, 0, x);
            if(*var != '$')
                second_part = ft_strjoin(first_part, getenv(var));
            else 
                second_part = ft_strjoin(first_part, ft_itoa(getpid()));
            //printf("second part: %s\n", second_part);            
            free(first_part);
            str += x +1 + ft_strlen(var);
            first_part = ft_strjoin(second_part, str);
            free(second_part);
            str = first_part;
            free(var);
            x = -1;
        }
         x++;
    }
    return(str);
}