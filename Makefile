NAME				=	minishell

libft				= 	libft
INC_DIR				= 	./includes/ 
						 
							 
CC 					= 	gcc
CFLAGS 				= 	-Wall -Werror -Wextra -g3  # -fsanitize=address
SRC_DIR				=	src
SOURCES				=	 $(SRC_DIR)/lexer.c \
						$(SRC_DIR)/fill_tokens.c \
						$(SRC_DIR)/expansor.c \
						$(SRC_DIR)/utils.c \
						$(SRC_DIR)/utils2.c \
						$(SRC_DIR)/environment.c \
						$(SRC_DIR)/fill_data.c \
						$(SRC_DIR)/redirections.c \
						$(SRC_DIR)/redirections_utils.c \
						$(SRC_DIR)/get_cmd_path.c \
						$(SRC_DIR)/double_red.c \
						$(SRC_DIR)/general_function.c \
						$(SRC_DIR)/fd_utils.c \
						$(SRC_DIR)/executor.c \
						$(SRC_DIR)/exec_utils.c \
						$(SRC_DIR)/builtin1.c		\
						$(SRC_DIR)/builtin2.c		\
						$(SRC_DIR)/signals.c\
						$(SRC_DIR)/exit.c\

OBJS				= 	$(SOURCES:.c=.o)


$(NAME): $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
	make -C $(libft)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include $(libft)/libft.a -o $(NAME)

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)   

all: $(NAME)

fclean : clean

	make fclean -C $(libft)
clean:
	rm -f $(OBJS) $(NAME)
re:	fclean all
.PHONY: all
