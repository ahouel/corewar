/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:24:05 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:24:10 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	sti(t_vm *vm, t_pcb *proc)
{
	int addr;
	int reg;

	if (!check_params(proc->op))
		return ;

	addr = (proc->op->ar[1] + proc->op->ar[2]) % IDX_MOD;
	addr = proc->op->pos_opcode + addr;

	reg = proc->op->ar[0];

	vm->ram[modulo(addr, MEM_SIZE)].mem = proc->reg[reg] >>24;
	vm->ram[modulo(addr, MEM_SIZE)].num = proc->uid;
	vm->ram[modulo(addr, MEM_SIZE)].flash = BLING_DELAY;

	vm->ram[modulo(addr + 1, MEM_SIZE)].mem = proc->reg[reg] >>16;
	vm->ram[modulo(addr + 1, MEM_SIZE)].num = proc->uid;
	vm->ram[modulo(addr + 1, MEM_SIZE)].flash = BLING_DELAY;


	vm->ram[modulo(addr + 2, MEM_SIZE)].mem = proc->reg[reg] >>8;
	vm->ram[modulo(addr + 2, MEM_SIZE)].num = proc->uid;
	vm->ram[modulo(addr + 2, MEM_SIZE)].flash = BLING_DELAY;


	vm->ram[modulo(addr + 3, MEM_SIZE)].mem = proc->reg[reg];
	vm->ram[modulo(addr + 3, MEM_SIZE)].num = proc->uid;
	vm->ram[modulo(addr + 3, MEM_SIZE)].flash = BLING_DELAY;

	if (0x4 & vm->verbosity)
	{
		show_operations(vm, proc);
		printf("\n       | -> store to %d + %d = %d (with pc and mod %d)\n", proc->op->ar[1], proc->op->ar[2], proc->op->ar[1] + proc->op->ar[2], addr);
	}
}
