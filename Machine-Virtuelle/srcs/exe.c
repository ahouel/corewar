/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:19:04 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:19:57 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	dump(t_vm *vm)
{
	if (!(vm->cycle % vm->dump))
		show_mem(vm);
}

void		exe(t_vm *vm)
{
	t_pcb	*proc;

	while (process_living(vm))
	{
		if (2 & vm->verbosity)
			printf("It is now cycle %d\n", vm->cycle + 1);
		if (vm->ncurses)
		{
			call_ncurses(vm);
			controller(vm);
			usleep(vm->delay);
		}
		proc = vm->proc;
		while (proc != NULL)
		{
			if (proc->state == 'R')
				idle_state(vm, proc);
			if (16 & vm->verbosity)
				show_pc_move(vm, proc);
			proc->last_pc = proc->pc;
			proc = proc->next;
		}
		vm->cycle++;
		if (vm->dump != -1 && !vm->ncurses)
			dump(vm);
	}
	if (vm->last_one)
		printf("Last_one => %s\n", vm->last_one->file_name);
}
