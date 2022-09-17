#include <stdlib.h>
#include "lexer.h"
#include <stdio.h>
int ft_count_char(char *str)
{
	int chars;

	chars = 0;
	while(*str)
	{
		if(*str != ' ')
			chars++;
		str++;
	}
	return(chars);
}

char *command_line(char *str)
{
	char *array = malloc(ft_count_char(str) * 2);
	char  *line = array;
	count_words(str, array);
	printf("La línea es: %s\n", line);
	printf("Original: %s\n", str);
	return(line);
}