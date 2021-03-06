# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahouel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 13:53:00 by ahouel            #+#    #+#              #
#    Updated: 2018/02/16 16:12:56 by ahouel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = ../asm

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
LIB_PATH = ../libft/

SRC_FILES = end_it.c \
			exit_free.c \
			free_champ.c \
			free_instructions.c \
			free_labs.c \
			free_op.c \
			free_tab.c \
			get_labels_params.c \
			get_ocp.c \
			header.c \
			is_label_char.c \
			itohex.c \
			label_chars.c \
			main.c \
			new_instruction.c \
			new_label.c \
			op.c \
			params.c \
			pars.c \

INC_FILES = asm.h \
			op.h

LIB_FILES = libft.a
LIB = $(addprefix $(LIB_PATH), $(LIB_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_EXEC = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all: $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) -c $< -o $@ -I $(INC_PATH) -I $(LIB_PATH)includes
	@echo "\033[34mCompilation of \033[1m$(notdir $<)\033[0m \033[34mdone.\033[0m"

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
