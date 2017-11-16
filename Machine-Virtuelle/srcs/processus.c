/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:23:07 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:33:48 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	kill_proc(t_vm *vm)
{
	t_pcb *tmp;

	tmp = vm->proc;
	while (tmp)
	{
		if ((vm->cycle - tmp->last_live) > vm->ctd && tmp->state == 'R')
		{
			tmp->state = 'Z';
			if (0x8 & vm->verbosity)
				printf("Process %d hasn't lived for %d cycles (CTD %d)\n", tmp->uid + 1, vm->cycle - tmp->last_live, vm->ctd);
		}
		tmp = tmp->next;
	}
}



void	undertaker(t_vm *vm)
{
	int i;
	t_pcb	*tmp;

	i = 1;
	tmp = vm->proc;
	while (i <= MAX_PLAYERS)
	{
		if (!vm->player[i].life_signal && vm->player[i].active)
		{
			vm->player[i].active = 0;
		}
		i++;
	}
	kill_proc(vm);
}

int		is_pc(t_vm *vm, int nb)
{
	t_pcb *tmp;

	tmp = vm->proc;
	while (tmp)
	{
		if (tmp->pc == nb && tmp->state == 'R')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		process_living(t_vm *vm)
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
		if (tmp->state == 'R')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
