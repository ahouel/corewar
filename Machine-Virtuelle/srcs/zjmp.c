/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:25:02 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:15:06 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	zjmp(t_vm *vm, t_pcb *proc)
{
	// printf(">>>>>>ENTER ZJMP<<<<<<   : Cycle > %d\n", vm->cycle);

	// printf("zjmp pos op => %d\n", proc->op->pos_opcode);
	// printf("ZJMP VALUE => %d\n", proc->op->ar[0]);
	if (proc->carry)
	{
		proc->pc = modulo(proc->op->pos_opcode + (proc->op->ar[0] % IDX_MOD), MEM_SIZE);
		proc->last_pc = proc->pc;
	}

	if (0x4 & vm->verbosity)
	{
		show_operations(vm, proc);
		if (proc->carry)
			printf(" OK");
		else
			printf(" FAILED");
		printf("\n");
	}
}
