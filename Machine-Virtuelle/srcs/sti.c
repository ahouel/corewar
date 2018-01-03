/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:24:05 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/03 14:32:05 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Montre l'operation sti avec -v 4
*/

static void	show_sti(t_pcb *proc, int *param, int addr)
{
	ft_printf("r%d %d %d\n", proc->op->param[0], param[0], param[1]);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			param[0], param[1], param[0] + param[1], addr);
}

/*
**	Transfert indirect Registre > RAM. Charge la valeur contenu dans le registre
**	passé en premier parametre a l'adresse resultante de l'addition des deux
**	derniers paramametres. Si cette valeur est nulle,
**	alors le carry passe a l'etat un, sinon a l'ettat zero.
*/

void		sti(t_vm *vm, t_pcb *proc)
{
	int addr;
	int	i;
	int	param[2];

	addr = 0;
	i = 0;
	while (++i < 3)
	{
		if (proc->op->param_type[i] == IND_CODE)
		{
			param[i - 1] = get_ind_value(vm,
					get_address(vm, proc, proc->op->param[i]));
		}
		else if (proc->op->param_type[i] == REG_CODE)
			param[i - 1] = proc->reg[proc->op->param[i] - 1];
		else
			param[i - 1] = proc->op->param[i];
		addr += param[i - 1];
	}
	addr = get_address(vm, proc, addr);
	store_ind_value(vm, addr, proc->reg[proc->op->param[0] - 1], proc->uid);
	proc->carry = (proc->reg[proc->op->param[0] - 1] ? 0 : 1);
	if (vm->verbosity & V_OP)
		show_sti(proc, param, addr);
}
