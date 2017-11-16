/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:23:36 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:32:42 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	st(t_vm *vm, t_pcb *proc)
{
	unsigned int	addr;

	if (!check_params(proc->op))
		return ;
	if (proc->op->ar_typ[1] == REG_CODE)
	{
		if (proc->op->ar[1] >= 1 && proc->op->ar[1] <= 16)
			proc->reg[proc->op->ar[1]] = proc->reg[proc->op->ar[0]];
	}
	else
	{
		addr = (proc->op->pos_opcode + (proc->op->ar[1] % IDX_MOD));

		addr = modulo(addr, MEM_SIZE);

		vm->ram[addr].mem = proc->reg[proc->op->ar[0]] >> 24;
		vm->ram[addr].num = proc->uid;
		vm->ram[addr].flash = 40;

		if (!vm->ncurses && vm->debug)
			printf("> : %x  ", vm->ram[addr].mem);

		addr = modulo(addr + 1, MEM_SIZE);
		vm->ram[addr].mem = proc->reg[proc->op->ar[0]] >> 16;
		vm->ram[addr].num = proc->uid;
		vm->ram[addr].flash = 40;

		if (!vm->ncurses && vm->debug)
			printf("> : %x  ", vm->ram[addr].mem);

		addr = modulo(addr + 1, MEM_SIZE);
		vm->ram[addr].mem = proc->reg[proc->op->ar[0]] >> 8;
		vm->ram[addr].num = proc->uid;
		vm->ram[addr].flash = 40;

		if (!vm->ncurses && vm->debug)
			printf("> : %x  ", vm->ram[addr].mem);

		addr = modulo(addr + 1, MEM_SIZE);
		vm->ram[addr].mem = proc->reg[proc->op->ar[0]];
		vm->ram[addr].num = proc->uid;
		vm->ram[addr].flash = 40;

		if (!vm->ncurses && vm->debug)
		{
			printf("> : %x  ", vm->ram[addr].mem);
			printf("\n");
		}
	}

	if (0x4 & vm->verbosity)
	{
		show_operations(vm, proc);
		printf("\n");
	}
}


//(PC + (42 % IDX_MOD)
