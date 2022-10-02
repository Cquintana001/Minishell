
#ifndef UTILS_H
# define UTILS_H
 
void free_d_array(char **array);
char *find_path(char **envp);
char *check_if_command(char **envp, char *str);
int file_exists(char *str);
int second_char_exists(char *str, char a);

#endif