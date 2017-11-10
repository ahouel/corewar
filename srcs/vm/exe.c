/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:53:05 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/10 14:55:15 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exe(t_vm *vm)
{
	t_proc	*proc;

	while (process_living(vm))
	{
		if (2 & vm->verbosity)
			printf("It is now cycle %d\n", vm->cycle + 1);

	//	ft_putstr("SEGV 1\n");
		//-------------------NCURSES
		if (vm->ncurses)
		{
			call_ncurses(vm);
			controller(vm);
			usleep(vm->delay);
		}
		//-------------------NCURSES
		// printf("RRRRRRRRRRRRRUUUUUUUUUUUNNNNNNNNNNNN   %d\n", vm->cycle);
		proc = vm->proc;
		while (proc != NULL)
		{
			if (proc->active)
			{
				// printf("SEGFFAULT_3\n");
			//	ft_putstr("SEGV 2\n");
				animate_proc(vm, proc);
			//	ft_putstr("SEGV 3\n");
			}
			//ft_putstr("bipbip\n");
			if (16 & vm->verbosity)
				show_pc_move(vm, proc);
			proc->last_pc = proc->pc;
			proc = proc->next;
		}
		vm->cycle++;
//-------------------------Debug

//-------------------------Debug
		// printf("%d\n", vm->dump);
		if (vm->dump != -1 && !vm->ncurses)
			dump(vm);
		// printf("SEGFFAULT_5\n");
		// printf("SEGV 4\n");
	//	ft_putstr("SEGV 4\n");
	}
//	printf("END\n");
	if (vm->last_one)
		printf("Last_one => %s\n", vm->last_one->file_name);
}
