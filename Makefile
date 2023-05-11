NAME        	= minishell

CC          	= cc

CFLAGS      	= -Wall -Wextra -Werror -g

INCLUDE     	= includes/

SRC_DIR     	= srcs
LIBFT_DIR  		= libft
OBJ_DIR     	= objs

SRCS        	= $(wildcard $(SRC_DIR)/*.c)
OBJS        	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_SRCS 	= $(wildcard $(LIBFT_DIR)/*.c)
OBJS_LIBFT 	= $(LIBFT_SRCS:$(LIBFT_DIR)/%.c=$(OBJ_DIR)/%.o)

READLINE_MAC    = -L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include

RM          	= rm -rf

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(LIBFT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(OBJS_LIBFT)
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) $(OBJS_LIBFT) -o $(NAME) $(READLINE_MAC)
	@echo "[+] $(NAME) compiled"

all: $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "[+] $(NAME) cleaned"

fclean: clean
	@$(RM) $(OBJ_DIR)/$(NAME)
	@echo "[+] $(NAME) fcleaned"

re: fclean all