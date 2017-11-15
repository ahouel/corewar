# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahouel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 13:53:00 by ahouel            #+#    #+#              #
#    Updated: 2017/11/15 15:52:02 by ahouel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

CC = clang
CFLAGS = -g
NAME = ../asm

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
LIB_PATH = ../libft/

SRC_FILES = main.c \
			create_file.c \
			error.c \
			labels.c \
			header.c \
			debug.c \
			op.c \
			find_op.c \
			parsing_tools.c \
			toolkit.c \
			analyse.c \
			analyse_tools.c \
			display1.c \
			display2.c \
			check_line.c \
			lex_ins1.c \
			lex_ins2.c \
			check_arg1.c \
			check_arg2.c \
			read_line.c \
			read_tools.c \
			verbose.c \
			free.c

INC_FILES = corewar.h
LIB_FILES = libft.a
LIB = $(addprefix $(LIB_PATH), $(LIB_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_EXEC = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all: $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH) -I $(LIB_PATH)includes
	@echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

$(LIB):
	@make -C $(LIB_PATH)

$(NAME): $(LIB) $(OBJ_PATH) $(OBJ_EXEC)
	@$(CC) $(CFLAGS) $(OBJ_EXEC) $(LIB) -o $(NAME) -I $(INC_PATH) -I $(LIB_PATH)includes
	@echo "\033[32mBinary \033[1;32m$(notdir $(NAME))\033[1;0m\033[32m created.\033[0m"

clean:
ifeq ("$(shell test -e $(OBJ_PATH) && echo titi)", "titi")
	@rm -rf $(OBJ_PATH)
	@echo "\033[31mObjects files of \033[1;31m$(notdir $(NAME))\033[1;0m\033[31m removed.\033[0m"
else
	@echo "\033[31mObjects files of \033[1;31m$(notdir $(NAME))\033[1;0m\033[31m not found.\033[0m"
endif

fclean: clean
ifeq ("$(shell test -e $(NAME) && echo toto)", "toto")
	@rm $(NAME)
	@echo "\033[31mBinary \033[1;31m$(notdir $(NAME))\033[1;0m\033[31m removed.\033[0m"
else
	@echo "\033[31mBinary \033[1;31m$(notdir $(NAME))\033[1;0m\033[31m not found.\033[0m"
endif

re: fclean all
