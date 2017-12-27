/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:20:07 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/21 16:53:56 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Montre l'operation ld avec -v 4
*/

static void	show_ld(t_pcb *proc)
{
	ft_printf("%d r%d\n", proc->reg[proc->op->param[1] - 1],
			proc->op->param[1]);
}

/*
**	Transfert direct RAM > Registre. Charge le premier parametre dans le
**	registre passé en second parametre. Si la valeur du premier
**	parametre est egale a zero, alors le carry passe a l'etat un, sinon a
**	l'etat zero.
*/

void		ld(t_vm *vm, t_pcb *proc)
{
	int	addr;

	if (proc->op->param_type[0] == IND_CODE)
	{
		addr = get_address(vm, proc, proc->op->param[0]);
		proc->reg[proc->op->param[1] - 1] = get_ind_value(vm, addr);
	}
	else
		proc->reg[proc->op->param[1] - 1] = proc->op->param[0];
	proc->carry = (proc->reg[proc->op->param[1] - 1] ? 0 : 1);
	if (vm->verbosity & V_OP)
		show_ld(proc);
}
