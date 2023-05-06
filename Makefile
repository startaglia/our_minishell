NAME		= minishell

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g

INCLUDE		= includes/

SRCS		= $(wildcard $(SRC_DIR)/*.c)

SRC_DIR		= srcs

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_DIR		= objs

READLINE	= -L/usr/include/readline -I/usr/include/readline -lreadline

RM			= rm -rf

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) -o $@ $(READLINE)
	@echo "[+] $(NAME) compiled"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "[+] $(NAME) cleaned"

fclean: clean
	@$(RM) $(NAME)
	@echo "[+] $(NAME) fcleaned"

re: fclean all