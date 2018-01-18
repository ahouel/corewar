/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:25:02 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/17 19:05:09 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Montre si le zjmp a reussit ou non avec -v 4
*/

static void	show_zjmp(t_pcb *proc)
{
	ft_printf("%d ", proc->op->param[0]);
	if (proc->carry)
		ft_printf("OK\n");
	else
		ft_printf("FAILED\n");
}

/*
**	Saute a l'adresse passé en parametre si le carry est a l'etat un.
**	L'adresse devient alors celle de la prochaine instruction.
**	Si le carry est a l'etat zero, rien ne se passe et le flot
**	continue normalement jusqu'a l'instruction suivante.
*/

void		zjmp(t_vm *vm, t_pcb *proc)
{
	if (proc->carry)
	{
		proc->pc = get_address(proc, proc->op->param[0]);
		while (proc->pc < 0)
			proc->pc += MEM_SIZE;
	}
	if (vm->verbosity & V_OP)
		show_zjmp(proc);
}
