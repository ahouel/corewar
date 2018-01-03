/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:23:36 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/03 19:38:12 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Montre l'operation ld avec -v 4
*/

static void	show_st(t_pcb *proc)
{
	ft_printf("r%d %d\n", proc->op->param[0],
			proc->op->param[1]);
}

/*
**	Transfert direct Registre > RAM / Registre. Charge le contenu du
**	registre passé en premier parametre dans le second parametre. Si la
**	valeur du premier parametre est egale a zero, alors le carry passe a
**	l'etat un, sinon a l'etat zero.
*/

void		st(t_vm *vm, t_pcb *proc)
{
	int addr;

	if (proc->op->param_type[1] == IND_CODE)
	{
		addr = get_address(vm, proc, proc->op->param[1]);
		store_ind_value(vm, addr, proc->reg[proc->op->param[0] - 1], proc->uid);
	}
	else
		proc->reg[proc->op->param[1] - 1] = proc->reg[proc->op->param[0] - 1];
	proc->carry = (proc->reg[proc->op->param[0] - 1] ? 1 : 0);
	if (vm->verbosity & V_OP)
		show_st(proc);
}
