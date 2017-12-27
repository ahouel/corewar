/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:25:02 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/27 15:43:35 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Montre si le zjmp a reussit ou non avec -v 4
*/

static void	show_zjmp(t_pcb *proc)
{
//	ft_printf("%d ", proc->op->param[0]);
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
//	ft_printf("le pc pendant le jump%d et le param[0]%d\n", proc->pc, proc->op->param[0]);
//	ft_printf("get_add %d\n", get_address(vm, proc, proc->op->param[0]));
	if (proc->carry)
		proc->pc = get_address(vm, proc, proc->op->param[0]) % MEM_SIZE;
	if (vm->verbosity & V_OP)
		show_zjmp(proc);
}
