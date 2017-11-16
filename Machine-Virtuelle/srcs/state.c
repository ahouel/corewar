/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:23:51 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:13:36 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// void	idle_state(t_vm *vm, t_proc *proc)
// {
// 	// printf("IDLE %d\n", vm->cycle);
//
// 	// printf("------------IDLE_STATE------------\n");
// 	// printf("SEGV_1\n");
// 	// printf("proc->pc = %d\n", proc->pc);
//
// 	if ((proc->op = create_op(vm, proc, vm->ram[proc->pc % MEM_SIZE].mem)))
// 	{
// 		// printf("proc num : %d   delay : %d\n", proc->id, proc->op->loadtime);
// 		proc->state = WAIT;
// 	}
// 	else
// 		proc->pc = (proc->pc + 1) % MEM_SIZE;
//
// }

void	idle_state(t_vm *vm, t_pcb *proc)
{
	if(!proc->op)
	{
		// printf("Here  %d\n", vm->ram[proc->pc % MEM_SIZE].mem);
		if (is_opcode(vm->ram[proc->pc % MEM_SIZE].mem))
		{
			proc->op = create_op(vm, proc, vm->ram[proc->pc % MEM_SIZE].mem);
		}
		else
		{
			proc->pc = (proc->pc + 1) % MEM_SIZE;
		}
	}
	else
	{
		// ft_putstr("SEGV 2\n");
		// if (proc->id == 5)
		// 	printf("reduce lifetime\n");
		proc->op->loadtime--;
		if (proc->op->loadtime <= 0)
		{
			//ft_putstr("SEGFFAULT_2\n");
			fill_cur_op(vm, proc);
			//ft_putstr("SEGFFAULT_3\n");
			if (op_tab[proc->op->code - 1].func != NULL)
			{
				op_tab[proc->op->code - 1].func(vm, proc);
			}
			proc->op = NULL;
			// printf("SEGFFAULT_3\n");
		}
		// ft_putstr("SEGV 3\n");
	}
	// ft_putstr("SEGV 4\n");
	// printf("SEGFFAULT_4\n");

}
