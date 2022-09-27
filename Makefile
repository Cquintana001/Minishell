NAME				=	minishell

libft				= 	libft
INC_DIR				= 	./includes/
CC 					= 	gcc
CFLAGS 				= 	-Wall -Werror -Wextra -g  
SRC_DIR				=	src
SOURCES				=	$(SRC_DIR)/prompt.c \
						$(SRC_DIR)/lexer.c \
						$(SRC_DIR)/lexer1.c \
						$(SRC_DIR)/fill_array.c \
						$(SRC_DIR)/expansor.c \
						 

OBJS				= 	$(SOURCES:.c=.o)


$(NAME): $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) 
	make -C $(libft)
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(libft)/libft.a -o $(NAME)

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

all: $(NAME)

fclean : clean

	make fclean -C $(libft)
clean:
	rm -f $(OBJS) $(NAME)
re:	fclean all
.PHONY: all