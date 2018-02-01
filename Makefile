# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahouel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 14:02:54 by ahouel            #+#    #+#              #
#    Updated: 2018/02/01 15:13:31 by ahouel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = CW
VM_NAME = corewar
ASM_NAME = asm
DASM_NAME = dasm
LIB_NAME = libft.a

VM_PATH = ./Machine-Virtuelle/
ASM_PATH = ./Assembleur/
LIB_PATH = ./libft/
LIB_NAME = libft.a
OBJS_PATHS = obj/

all: $(NAME)

$(NAME): $(VM_NAME) $(ASM_NAME)

$(VM_NAME):
	@echo "\033[35mCompiling \033[1m$(notdir $(VM_NAME))\033[0m\033[35m...\033[0m"
	@make -C $(VM_PATH)

$(ASM_NAME):
	@echo "\033[35mCompiling \033[1m$(notdir $(ASM_NAME))\033[0m\033[35m...\033[0m"
	@make -C $(ASM_PATH)

clean:
	@make -C $(LIB_PATH) clean
ifeq ("$(shell test -e $(VM_PATH)$(OBJS_PATHS) && echo toto)", "toto")
	@make -C $(VM_PATH) clean
endif
ifeq ("$(shell test -e $(ASM_PATH)$(OBJS_PATHS) && echo tata)", "tata")
	@make -C $(ASM_PATH) clean
endif

fclean: clean
	@rm -f $(LIB_PATH)$(LIB_NAME)
ifeq ("$(shell test -e $(VM_NAME) && echo toti)", "toti")
	@rm -f $(VM_NAME)
	@echo "\033[31mBinary \033[1;31m$(notdir $(VM_NAME))\033[1;0m\033[31m removed.\033[0m"
endif
ifeq ("$(shell test -e $(ASM_NAME) && echo toty)", "toty")
	@rm -f $(ASM_NAME)
	@echo "\033[31mBinary \033[1;31m$(notdir $(ASM_NAME))\033[1;0m\033[31m removed.\033[0m"
endif

re: fclean all
