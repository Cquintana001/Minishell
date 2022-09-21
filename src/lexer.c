

/* static char *space_trim(char *str)
{
    
    while(*str == ' ' && *str)
        str++;
    return(str);
}
static int second_char_exists(char *str, char a)
{
    char *array;

    array = ++str;
    while(*array)
    {
        if(*array == a)
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
        if(*str == '"' && second_char_exists(str, '"'))
            return(str);
        str++;
    }
    return(str);
}

static char *find_next_char(char *str, char a)
{
    static char *array;

    array = (str + 1);
    while(*array)
    {
        if(*array == a)
            return(++array);
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
        if(*str == '"' && second_char_exists(str, '"'))
           {
             str = find_next_char(str, '"');
             x++;
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
		else if(*str == ' ')
            str = space_trim(str);
		else if (*str)
        {
                x++;
               str =  word_trim(str);
        }		 
	}
	return (x);
}
 */




 