/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:20:23 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:10:33 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	get_indirect(t_vm *vm, t_op *op, int nb_arg)
{
	int	value;
	int	pos;

	value = 0x0;
	pos = op->pos_opcode + (op->ar[nb_arg] % IDX_MOD);
	// printf("POS LDI %d\n", pos);
	value |= (unsigned char)vm->ram[modulo(pos, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(pos + 1, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(pos + 2, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(pos + 3, MEM_SIZE)].mem;

	return (value);
}

void		ldi(t_vm *vm, t_pcb *proc)
{
	unsigned int		addr;
	unsigned int		reg_nb;
	int ar1;
	int ar2;
	int value;

	value = 0x0;
	addr = 0;

	if (!check_params(proc->op))
		return ;

	if (proc->op->ar_typ[0] == REG_CODE)
	{
		// printf("reg %d\n", proc->op->ar[0]);
		proc->op->ar[0] = proc->reg[proc->op->ar[0]];
	}
	else if (proc->op->ar_typ[0] == IND_CODE)// IND CODE
	{
		proc->op->ar[0] = get_indirect(vm, proc->op, 0);
		printf("ar1 IND => %d\n", proc->op->ar[0]);
		// ar1 = vm->ram[].mem         proc->op->pos_opcode
	}

	if (proc->op->ar_typ[1] == REG_CODE && !check_reg(proc->op->ar[1]))
		return ;
	if (proc->op->ar_typ[1] == REG_CODE)
	{
		// printf("reg %d\n", proc->op->ar[1]);
		proc->op->ar[1] = proc->reg[proc->op->ar[1]];
	}

	addr = (proc->op->ar[0] + proc->op->ar[1]) % IDX_MOD;
	addr = addr + proc->op->pos_opcode;

	value |= (unsigned char)vm->ram[modulo(addr, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(addr + 1, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(addr + 2, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(addr + 3, MEM_SIZE)].mem;

	if (proc->op->ar_typ[2] == REG_CODE && !check_reg(proc->op->ar[2]))
		return ;
	proc->reg[proc->op->ar[2]] = value;

	if (0x4 & vm->verbosity)
	{
		show_operations(vm, proc);
		printf("\n| -> load from %d + %d = %d (with pc and mod %d)", proc->op->ar[0], proc->op->ar[1], value, addr);
		printf("\n");
	}

}
