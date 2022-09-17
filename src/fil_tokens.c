#include "lexer.h"
#include "length.h"

int copy_quotes(char *str, char *array)
{
	
}

char *fill_tokens(char *str, int space)
{
	 
	int x;
	char *array;

	x = ft_count_char(str);

	array = (char*)malloc((x + space) * sizeof(char)); 
	while(*str)
	{
		if(*str == ' ')
			str = space_trim(str);
		if(*str == '"' && second_char_exists(str, '"'))
    	{
    	   *array = *str;
		   while
    	}
    	else if(*str == '\'' && second_char_exists(str, '\''))
    	   {
    	     str = find_next_char(str, '\'');
    	     x++;
    	   }
    	else if(*str == '|' || *str == '<' || *str == '>')
    	{
    	    str++;
    	    x++;
    	}
 
		else if (*str)
    	{
    	        x++;
    	       str =  word_trim(str);
    	}
	}	 




}