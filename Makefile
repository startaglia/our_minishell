# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 12:48:07 by startagl          #+#    #+#              #
#    Updated: 2023/06/11 11:51:08 by scastagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        	= minishell

CC          	= cc

CFLAGS      	= -Wall -Wextra -Werror -g -fcommon -fsanitize=address

INCLUDE     	= includes/

SRC_DIR     	= srcs
SYNTAX_DIR  	= srcs/syntax
PARSING_DIR  	= srcs/parsing
EXECUTOR_DIR	= srcs/executor
LIBFT_DIR		= includes/libft
OBJ_DIR     	= objs

PRINTF			= printf
SRCS        	= $(wildcard $(SRC_DIR)/*.c)
OBJS        	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SYNTAX_SRCS 	= $(wildcard $(SYNTAX_DIR)/*.c)
OBJS_SYNTAX 	= $(SYNTAX_SRCS:$(SYNTAX_DIR)/%.c=$(OBJ_DIR)/%.o)

PARSING_SRCS 	= $(wildcard $(PARSING_DIR)/*.c)
OBJS_PARSING 	= $(PARSING_SRCS:$(PARSING_DIR)/%.c=$(OBJ_DIR)/%.o)

EXECUTOR_SRCS 	= $(wildcard $(EXECUTOR_DIR)/*.c)
OBJS_EXECUTOR 	= $(EXECUTOR_SRCS:$(EXECUTOR_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_SRCS 	= $(wildcard $(LIBFT_DIR)/*.c)
OBJS_LIBFT 	= $(LIBFT_SRCS:$(LIBFT_DIR)/%.c=$(OBJ_DIR)/%.o)

READLINE        = -L/usr/include/readline -I/usr/include/readline -lreadline
READLINE_MAC    = -L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include

RM          	= rm -rf

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(SYNTAX_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(PARSING_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(EXECUTOR_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o : $(LIBFT_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(OBJS_SYNTAX) $(OBJS_PARSING) $(OBJS_EXECUTOR) $(OBJS_LIBFT)
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) $(OBJS_SYNTAX) $(OBJS_PARSING) $(OBJS_EXECUTOR) $(OBJS_LIBFT) -o $(NAME) $(READLINE_MAC)
	@echo "[+] $(NAME) compiled"

all:	$(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "[+] $(NAME) cleaned"

fclean: clean
	@$(RM) $(NAME)
	@echo "[+] $(NAME) fcleaned"

re: fclean all
