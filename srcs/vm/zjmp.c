/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 21:03:43 by lchety            #+#    #+#             */
/*   Updated: 2017/11/04 16:01:15 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	zjmp(t_vm *vm, t_proc *proc)
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