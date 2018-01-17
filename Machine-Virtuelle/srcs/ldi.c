/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:53:09 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/17 19:06:07 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Montre l'operation ldi avec -v 4
*/

static void	show_ldi(t_pcb *proc, int *param, int addr)
{
	ft_printf("%d %d r%d\n", param[0], param[1], proc->op->param[2]);
	ft_printf("       | -> load from %d + %d = %d (with pc ",
			param[0], param[1], param[0] + param[1]);
	if (proc->op->addr_rest)
		ft_printf("and mod %d)\n", addr);
	else
		ft_printf("%d)\n", addr);
}

/*
**	Transfert indirect RAM > Registre. Charge la valeur a l'adresse resultante
**	de l'addition des deux premiers parametres dans le registre
**	passé en troisieme parametre. Si cette valeur est nulle,
**	alors le carry passe a l'etat un, sinon a l'ettat zero.
*/

void		ldi(t_vm *vm, t_pcb *proc)
{
	int	addr;
	int	i;
	int	param[2];

	i = -1;
	addr = get_address(proc, 0);
	while (++i < 2)
	{
		if (proc->op->param_type[i] == IND_CODE)
			param[i] = get_ind_value(vm,
					get_address(proc, proc->op->param[i]));
		else if (proc->op->param_type[i] == REG_CODE)
			param[i] = proc->reg[proc->op->param[i] - 1];
		else
			param[i] = proc->op->param[i];
		addr += param[i];
	}
	proc->reg[proc->op->param[2] - 1] = get_ind_value(vm, addr);
	proc->carry = (proc->reg[proc->op->param[2] - 1] ? 0 : 1);
	if (vm->verbosity & V_OP)
		show_ldi(proc, param, addr);
}
