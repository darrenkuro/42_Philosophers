# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 11:24:01 by dlu               #+#    #+#              #
#    Updated: 2023/06/15 02:18:27 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo

SRCDIR	:=	srcs
_SRC	:=	main.c utils.c action.c
SRC		:=	$(addprefix $(SRCDIR)/, $(_SRC))

OBJDIR	:=	objs
_OBJ	:=	$(_SRC:.c=.o)
OBJ		:=	$(addprefix $(OBJDIR)/, $(_OBJ))

CC		:=	cc
RM		:=	/bin/rm -f
#CFLAGS	:=	-Wall -Wextra -Werror -g -fsanitize=thread
CFLAGS	:=	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): init $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

init:
	@mkdir -p $(OBJDIR)

.phony: all clean flcean re init
