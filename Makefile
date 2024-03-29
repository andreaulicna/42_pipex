# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 13:27:38 by aulicna           #+#    #+#              #
#    Updated: 2024/03/17 14:43:45 by aulicna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_B = pipex_bonus

SRC = 	src/main.c \
		src/command.c \
		src/free_error.c \
		src/input.c

SRC_B = src_bonus/main_bonus.c \
		src_bonus/command_bonus.c \
		src_bonus/free_error_bonus.c \
		src_bonus/input_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

HEADER = incl/pipex.h
HEADER_B = incl/pipex_bonus.h

LIBFTPRINTF = libftprintf
LIBFT = libftprintf/libft

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

all: libs $(NAME)
	@echo "pipex executable ready ✅"

bonus: libs $(NAME_B)
	@echo "pipex_bonus executable ready ✅"

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -L $(LIBFTPRINTF) -o $@ $^ -lftprintf

$(NAME_B): $(OBJ_B) $(HEADER_B)
	$(CC) $(CFLAGS) -L $(LIBFTPRINTF) -o $@ $^ -lftprintf

libs:
	@make -C $(LIBFTPRINTF)
	@echo "libprintf library ready ✅"

clean:
	@rm -f $(OBJ)
	@rm -f $(OBJ_B)
	@make clean -C $(LIBFTPRINTF)

fclean:
	@rm -f $(OBJ)
	@rm -f $(OBJ_B)
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@make fclean -C $(LIBFTPRINTF)

re: fclean all

bonus_re: fclean bonus

.PHONY: all bonus libs clean fclean re