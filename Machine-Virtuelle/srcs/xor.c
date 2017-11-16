/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:24:46 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:14:21 by ahouel           ###   ########.fr       */
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

void	xor(t_vm *vm, t_pcb *proc)
{
	unsigned int	ar1;
	unsigned int	ar2;

	if (proc->op->ar_typ[0] == T_REG)
	{
		if (proc->op->ar[0] <= 16 && proc->op->ar[0] >= 1)
		{
			proc->op->ar[0] = proc->reg[proc->op->ar[0]];
			proc->op->ar_typ[0] = T_IND;
		}
	}
	else if (proc->op->ar_typ[0] == T_IND)
	{
		proc->op->ar[0] = get_indirect(vm, proc->op, 0);
	}

	if (proc->op->ar_typ[1] == T_REG)
	{
		if (proc->op->ar[1] <= 16 && proc->op->ar[1] >= 1)
		{
			proc->op->ar[1] = proc->reg[proc->op->ar[1]];
			proc->op->ar_typ[1] = T_IND;
		}
	}
	else
		proc->op->ar[1] = get_indirect(vm, proc->op, 0);


	proc->reg[proc->op->ar[2]] = proc->op->ar[0] ^ proc->op->ar[1];

	if (0x4 & vm->verbosity)
	{
		show_operations(vm, proc);
		printf("\n");
	}
}
