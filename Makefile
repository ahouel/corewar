# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahouel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 14:02:54 by ahouel            #+#    #+#              #
#    Updated: 2018/02/16 16:25:43 by ahouel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, norme

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
SRC_VM =	main.c					\
			initialisation.c		\
			init_vm.c				\
			exe.c					\
			error.c					\
			free_vm.c				\
			get_winner.c			\
			check_arg.c				\
			new_player.c			\
			swap_players.c			\
			write_players.c			\
			srch_player.c			\
			load_op.c				\
			ocp_is_valid.c			\
			get_ind_value.c			\
			get_address.c			\
			move_processus.c		\
			create_processus.c		\
			print_ram.c				\
			store_ind_value.c		\
			op.c					\
			live.c					\
			ld.c					\
			st.c					\
			add.c					\
			sub.c					\
			gates.c					\
			zjmp.c					\
			ldi.c					\
			sti.c					\
			ft_fork.c				\
			aff.c					\
			init_ncurses.c			\
			ncurses_colors_init.c	\
			print_aff.c				\
			ncurses_stats.c			\
			ncurses_pairs.c			\
			refresh_ncurses.c		\
			ncurses_controller.c	\
			call_ncurses.c

INC_VM =	vm.h					\
			op.h					\
			vm_struct.h

VM_ALL = $(addprefix $(VM_PATH)srcs/, $(SRC_VM)) $(addprefix $(VM_PATH)includes/, $(INC_VM))

SRC_ASM = 	end_it.c 				\
			exit_free.c 			\
			free_champ.c			\
			free_instructions.c		\
			free_labs.c				\
			free_op.c				\
			free_tab.c				\
			get_labels_params.c		\
			get_ocp.c				\
			header.c				\
			is_label_char.c			\
			itohex.c				\
			label_chars.c			\
			main.c					\
			new_instruction.c		\
			new_label.c				\
			op.c					\
			params.c				\
			pars.c

INC_ASM =	asm.h \
			op.h

ASM_ALL = $(addprefix $(ASM_PATH)srcs/, $(SRC_ASM)) $(addprefix $(ASM_PATH)includes/, $(INC_ASM))

all: $(NAME)

$(NAME): $(VM_NAME) $(ASM_NAME)

$(VM_NAME): $(VM_ALL)
	@echo "\033[35mCompiling \033[1m$(notdir $(VM_NAME))\033[0m\033[35m...\033[0m"
	@make -C $(VM_PATH)

$(ASM_NAME): $(ASM_ALL)
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

norme:
	@echo "\033[35mChecking the norme...\033[0m"
	@norminette $(ASM_ALL) $(VM_ALL)
