# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 10:49:25 by dcarassi          #+#    #+#              #
#    Updated: 2023/01/22 22:32:45 by dcarassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB1 = ar -rcs
LIB2 = ranlib
RM = rm -f
NAME = libft.a
INCLUDE = libft.h
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJS = $(SRCS:.c=.o)

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUSOBJS = $(BONUS:.c=.o)

all:	$(OBJS) $(NAME)

$(OBJS):	$(INCLUDE)

$(NAME):	$(OBJS) $(INCLUDE)
	$(LIB1) $(NAME) $(OBJS)
	$(LIB2) $(NAME)

clean:
	@$(RM) $(OBJS) $(BONUSOBJS)

fclean:	clean
	@$(RM) $(NAME)

re: fclean all

bonus: $(BONUSOBJS)
	@$(LIB1) $(NAME) $(BONUSOBJS)
