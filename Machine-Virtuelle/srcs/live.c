/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:20:53 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/20 10:55:49 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	live(t_vm *vm, t_pcb *proc)
{
	if (!vm->ncurses && vm->debug)
		printf(">>>>>ENTER_LIVE<<<<< : Cycle > %d\n", vm->cycle);
	int		num;

//	vm->lives_in_cycle++;
	proc->last_live = vm->cycle + 1;

	num = 0;
	// printf("NUM player => %d\n", proc->op->ar[0]);

//	if (!vm->ncurses && vm->debug)
//	{
//		printf("opcode pos : %d\n", proc->op->pos_opcode);
//		printf("fuck num %d\n", (int)proc->op->ar[0]);
//		printf("fuck num %x\n", (int)proc->op->ar[0]);
//	}
//	num = proc->op->ar[0] * -1;

	// printf("fuck num %d\n", num);
	if (4 & vm->verbosity)
	{
		show_operations(vm, proc);
		printf("\n");
	}

	if (num >= 1 && num <= vm->nb_player)
	{
		// printf("LIVE HERE ##################################\n");
		vm->player[num].life_signal++;
		vm->player[num].last_live = vm->cycle;
//		vm->ram[proc->op->pos_opcode].live = BLING_LIVE;
		if (5 & vm->verbosity)
			printf("Player %d (helltrain) is said to be alive\n", num);
	}

}
