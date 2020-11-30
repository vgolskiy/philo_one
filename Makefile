# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 12:32:07 by mskinner          #+#    #+#              #
#    Updated: 2020/11/30 12:32:11 by mskinner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# RESOURSES
SRC = eat_with_forks.c	main.c	parallelize.c	parse_initialize.c	print_message.c	support1.c	support2.c	support3.c
HEADER = phil.h
OBJ = $(SRC:.c=.o)

# COMPILATION
CC = gcc
PHREAD = -lpthread
FLAG = -Wall -Wextra -Werror
NAME = philo_one

%.o: %.c
	$(CC) $(FLAG) -I $(HEADER) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(PHREAD) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all re fclean clean 