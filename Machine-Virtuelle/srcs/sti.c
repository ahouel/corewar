/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 20:54:19 by lchety            #+#    #+#             */
/*   Updated: 2017/11/07 18:15:59 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sti(t_vm *vm, t_proc *proc)
{
	int addr;
	int reg;

	if (!check_params(proc->op))
		return ;

	addr = (proc->op->ar[1] + proc->op->ar[2]) % IDX_MOD;
	addr = proc->op->pos_opcode + addr;

	reg = proc->op->ar[0];

	vm->ram[modulo(addr, MEM_SIZE)].mem = proc->reg[reg] >>24;
	vm->ram[modulo(addr, MEM_SIZE)].num = proc->num;
	vm->ram[modulo(addr, MEM_SIZE)].blingbling = BLING_DELAY;

	vm->ram[modulo(addr + 1, MEM_SIZE)].mem = proc->reg[reg] >>16;
	vm->ram[modulo(addr + 1, MEM_SIZE)].num = proc->num;
	vm->ram[modulo(addr + 1, MEM_SIZE)].blingbling = BLING_DELAY;


	vm->ram[modulo(addr + 2, MEM_SIZE)].mem = proc->reg[reg] >>8;
	vm->ram[modulo(addr + 2, MEM_SIZE)].num = proc->num;
	vm->ram[modulo(addr + 2, MEM_SIZE)].blingbling = BLING_DELAY;


	vm->ram[modulo(addr + 3, MEM_SIZE)].mem = proc->reg[reg];
	vm->ram[modulo(addr + 3, MEM_SIZE)].num = proc->num;
	vm->ram[modulo(addr + 3, MEM_SIZE)].blingbling = BLING_DELAY;

	if (0x4 & vm->verbosity)
	{
		show_operations(vm, proc);
		printf("\n       | -> store to %d + %d = %d (with pc and mod %d)\n", proc->op->ar[1], proc->op->ar[2], proc->op->ar[1] + proc->op->ar[2], addr);
	}
}
