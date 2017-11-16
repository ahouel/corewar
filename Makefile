# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahouel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 14:02:54 by ahouel            #+#    #+#              #
#    Updated: 2017/11/16 10:03:58 by ahouel           ###   ########.fr        #
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
DASM_PATH = ./Desassembleur/
LIB_PATH = ./libft/
OBJS_PATHS = obj/

all: $(NAME)

$(NAME): $(VM_NAME) $(ASM_NAME) $(DASM_NAME)

$(VM_NAME):
	@echo "\033[34mCompilation of \033[36m$(notdir $(VM_NAME))\033[34m...\033[0m"
	@make -C $(VM_PATH)

$(ASM_NAME):
	@echo "\033[34mCompilation of \033[36m$(notdir $(ASM_NAME))\033[34m...\033[0m"
	@make -C $(ASM_PATH)

$(DASM_NAME):
	@echo "\033[34mCompilation of \033[36m$(notdir $(DASM_NAME))\033[34m...\033[0m"
	@make -C $(DASM_PATH)

clean:
	@make -C $(LIB_PATH) clean
ifeq ("$(shell test -e $(VM_PATH)$(OBJS_PATHS) && echo toto)", "toto")
	@make -C $(VM_PATH) clean
endif
ifeq ("$(shell test -e $(ASM_PATH)$(OBJS_PATHS) && echo tata)", "tata")
	@make -C $(ASM_PATH) clean
endif
ifeq ("$(shell test -e $(DASM_PATH)$(OBJS_PATHS) && echo titi)", "titi")
	@make -C $(DASM_PATH) clean
endif

fclean:
	@make -C $(LIB_PATH) fclean
ifeq ("$(shell test -e $(VM_NAME) && echo toti)", "toti")
	@make -C $(VM_PATH) fclean
endif
ifeq ("$(shell test -e $(ASM_NAME) && echo toty)", "toty")
	@make -C $(ASM_PATH) fclean
endif
ifeq ("$(shell test -e $(DASM_NAME) && echo totu)", "totu")
	@make -C $(DASM_PATH) fclean
endif

re: fclean all
