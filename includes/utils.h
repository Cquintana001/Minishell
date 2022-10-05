
#ifndef UTILS_H
# define UTILS_H
 
typedef struct s_data{

	char **cmd;
	char **redirection;
	char *path;
	int input;
	int output;	
 
	 

} t_data;

void free_d_array(char **array);
char *find_path(char **envp);
char *check_if_command(char **envp, char *str);
int file_exists(char *str);
int second_char_exists(char *str, char a);
#endif