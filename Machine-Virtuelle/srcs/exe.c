/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:19:04 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/24 11:54:14 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	processus_living(t_vm *vm)
{
	int		i;
	t_pcb	*tmp;

	i = 0;
	tmp = vm->proc;
	if (vm->cycle < vm->next_ctd)
		return (1);
	kill_proc(vm);
	set_ctd(vm);
	vm->next_ctd = vm->cycle + vm->ctd;
	while (tmp)
	{
		if (tmp->state != DEAD)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	dump(t_vm *vm)
{
	if (!(vm->cycle % vm->dump))
		print_ram(vm);
}

void		exe(t_vm *vm)
{
	t_pcb	*proc;

	while (processus_living(vm))
	{
		if (2 & vm->verbosity)
			ft_printf("It is now cycle %d\n", vm->cycle + 1);
		if (vm->ncurses)
		{
			call_ncurses(vm);
			controller(vm);
			usleep(vm->delay);
		}
		proc = vm->proc;
		while (proc)
		{
			if (proc->state == RUN)
				move_processus(vm, proc);
			if (16 & vm->verbosity)
				show_pc_move(vm, proc);
			proc->last_pc = proc->pc;
			proc = proc->next;
		}
		if (vm->debug == 3)
		{
			show_ops(vm);
			break ;
		}
		vm->cycle++;
		if (vm->dump != -1 && !vm->ncurses && vm->cycle == vm->dump)
		{
			print_ram(vm);
			exit(EXIT_SUCCESS);
		}
	}
	if (vm->last_one)
		ft_printf("Last_one => %s\n", vm->last_one->file_name);
}
