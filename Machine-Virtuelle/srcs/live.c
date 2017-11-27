/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:20:53 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/27 14:00:18 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_live(t_vm *vm, t_pcb *proc, int i)
{
	if (vm->verbosity & 1)
		ft_printf("Player %d (%s) is said to be alive\n", i, vm->player[i - 1].name);
}

void	live(t_vm *vm, t_pcb *proc)
{
	int	i;

	i = (int)proc->op->param[0];
	proc->last_live = vm->cycle + 1;
	i = -i;
	if (i < 0 || i > MAX_PLAYERS - 1)
		return ;
	if (!vm->player[i - 1].active)
		return ;
	vm->player[i - 1].life_signal++;
	vm->player[i - 1].last_live = vm->cycle;
	print_live(vm, proc, i);
}
