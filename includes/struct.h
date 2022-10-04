

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>

typedef struct s_data{

	char **cmd;
	char **redirection;
	char *path;
	int input;
	int output;	
	struct s_data *next;

} t_data;

t_data	*ft_lstnew1(int x);
#endif