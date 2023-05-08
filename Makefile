# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: startagl <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 12:48:07 by startagl          #+#    #+#              #
#    Updated: 2023/05/08 14:03:48 by startagl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        	= minishell

CC          	= cc

CFLAGS      	= -Wall -Wextra -Werror -g

INCLUDE     	= includes/

SRC_DIR     	= srcs
SYNTAX_DIR  	= srcs/syntax
MLIBFT_DIR  	= includes/mini_libft
OBJ_DIR     	= objs

SRCS        	= $(wildcard $(SRC_DIR)/*.c)
OBJS        	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SYNTAX_SRCS 	= $(wildcard $(SYNTAX_DIR)/*.c)
OBJS_SYNTAX 	= $(SYNTAX_SRCS:$(SYNTAX_DIR)/%.c=$(OBJ_DIR)/%.o)

MLIBFT_SRCS 	= $(wildcard $(MLIBFT_DIR)/*.c)
OBJS_MLIBFT 	= $(MLIBFT_SRCS:$(MLIBFT_DIR)/%.c=$(OBJ_DIR)/%.o)

READLINE        = -L/usr/include/readline -I/usr/include/readline -lreadline
READLINE_MAC    = -L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include

RM          	= rm -rf

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(SYNTAX_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(MLIBFT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(OBJS_SYNTAX) $(OBJS_MLIBFT)
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) $(OBJS_SYNTAX) $(OBJS_MLIBFT) -o $(NAME) $(READLINE_MAC)
	@echo "[+] $(NAME) compiled"

all: $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "[+] $(NAME) cleaned"

fclean: clean
	@$(RM) $(OBJ_DIR)/$(NAME)
	@echo "[+] $(NAME) fcleaned"

re: fclean all
