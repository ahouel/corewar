/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:17:17 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/21 16:53:45 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Montre l'operation add avec -v 4
*/

static void	show_add(t_pcb *proc)
{
	ft_printf("r%d r%d r%d\n", proc->op->param[0],
			proc->op->param[1], proc->op->param[2]);
}

/*
**	Ajoute le second parametre au premier parametre,
**	et stock le resultat dans le troisieme parametre.
**	Si la valeur resultante est egale a zero,
**	alors le carry passe a l'etat un, sinon a l'etat zero.
*/

void		add(t_vm *vm, t_pcb *proc)
{
	if (!(proc->reg[proc->op->param[2] - 1] = proc->reg[proc->op->param[0] - 1]
				+ proc->reg[proc->op->param[1] - 1]))
		proc->carry = 1;
	else
		proc->carry = 0;
	if (vm->verbosity & V_OP)
		show_add(proc);
}
