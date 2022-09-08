

static char *space_trim(char *str)
{
    
    while(*str == ' ' && *str)
        str++;
    return(str);
}
static int second_quote_exists(char *str)
{
    char *array;

    array = ++str;
    while(*array)
    {
        if(*array == '"')
            return(1);
        array++;
    }
    return(0);
}
static char *word_trim(char *str)
{
    str++;
    while(*str != ' ' && *str)
    {
        if(*str == '"' && second_quote_exists(str))
            return(str);
        str++;
    }
    return(str);
}

static char *find_next_quote(char *str)
{
    static char *array;

    array = ++str;
    while(*array)
    {
        if(*array == '"')
            return(array);
        array++;
    }
    return(str);
}


int	count_words( char *str)
{
	int	x;
 

	x = 0;
 
	while (*str)
	{
        if(*str == '"' && second_quote_exists(str))
           {
             str = find_next_quote(str);
             x++;
                if(!*(++str))
                    break ;
           }
		else if(*str == ' ')
			{
               str = space_trim(str);
            }
		else if (*str)
        {
                x++;
               str =  word_trim(str);
        }
		 
	}
	return (x);
}





 