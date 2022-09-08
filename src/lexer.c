
static int second_quote_exists(char *str)
{
    char *array;

    array = str;
    while(*array)
    {
        if(*array == '"')
            return(1);
        array++;
    }
    return(0);
}

static char *find_next_quote(char *str)
{
    static char *array;

    array = ++str;
    while(*array)
    {
        if(*array == '"')
            return(++array);
        array++;
    }
    return(str);
}


int	count_words( char *str)
{
	int	x;
	int	checkw;

	x = 0;
	checkw = 0;
	while (*str)
	{
        if(*str == '"' && second_quote_exists(str))
           {
             str = find_next_quote(str);
             x++;
           }
        if(!*str)
            break ;
		if(*str != ' ' && checkw == 0)
			{
                checkw = 1;
                x++;
            }
		else if (*str == ' ')
			checkw = 0;
		str++;
	}
	return (x);
}





 