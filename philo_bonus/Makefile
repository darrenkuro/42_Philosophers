# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 11:24:01 by dlu               #+#    #+#              #
#    Updated: 2023/06/18 22:19:54 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo_bonus

SRCDIR	:=	srcs
_SRC	:=	main.c utils.c action.c init.c
SRC		:=	$(addprefix $(SRCDIR)/, $(_SRC))

OBJDIR	:=	objs
_OBJ	:=	$(_SRC:.c=.o)
OBJ		:=	$(addprefix $(OBJDIR)/, $(_OBJ))

CC		:=	cc
RM		:=	/bin/rm -rf
CFLAGS	:=	-Wall -Wextra -Werror -g -fsanitize=thread
#CFLAGS	:=	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(OBJDIR)
	$(RM) $(NAME)

re: fclean all

.phony: all clean flcean re
