# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahouel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 10:03:32 by ahouel            #+#    #+#              #
#    Updated: 2017/11/16 15:01:09 by ahouel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

CC = clang
CFLAGS = -g
NAME = ../corewar

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
LIB_PATH = ../libftt/

SRC_FILES =	main.c \
			initialisation.c	\
			exe.c	\
			error.c	\
			check_arg.c	\
			controller.c	\
			cycle_to_die.c	\
			check_inst.c	\
			add_process.c	\
			debug.c	\
			write_players.c	\
			ft_strargv.c \
			srch_players.c \
			sti.c	\
			ld.c	\
			ldi.c	\
			live.c	\
			add.c	\
			and.c	\
			ncurses.c	\
			pars_op.c	\
			players.c	\
			processus.c	\
			create_processus.c \
			fork.c \
			or.c \
			xor.c \
			sub.c \
			st.c \
			state.c	\
			zjmp.c \
			op.c \
			lld.c

INC_FILES = vm.h op.h vm_struct.h
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
	@$(CC) $(CFLAGS) $(OBJ_EXEC) $(LIB) -o $(NAME) -I $(INC_PATH) -I $(LIB_PATH)includes -lncurses
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
