/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:17:41 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/17 19:04:55 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Montre l'operation and/or/xor avec -v 4
*/

static void	show_gates(t_pcb *proc, int *param)
{
	ft_printf("%d %d r%d\n", param[0],
			param[1], proc->op->param[2]);
}

/*
**	Effectue un AND/OR/XOR logique entre les deux premiers paramametres et
**	stock le resultat dans le troisieme paramametre.
**	Si la valeur resultante est egale a zero,
**	alors le carry passe a l'etat un, sinon a l'etat zero.
*/

void		gates(t_vm *vm, t_pcb *proc)
{
	int	param[2];
	int	i;

	i = -1;
	while (++i < 2)
	{
		if (proc->op->param_type[i] == IND_CODE)
			param[i] = get_ind_value(vm,
					get_address(proc, proc->op->param[i]));
		else if (proc->op->param_type[i] == REG_CODE)
			param[i] = proc->reg[proc->op->param[i] - 1];
		else
			param[i] = proc->op->param[i];
	}
	if (proc->op->code == 6)
		proc->reg[proc->op->param[2] - 1] = param[0] & param[1];
	if (proc->op->code == 7)
		proc->reg[proc->op->param[2] - 1] = param[0] | param[1];
	if (proc->op->code == 8)
		proc->reg[proc->op->param[2] - 1] = param[0] ^ param[1];
	proc->carry = (proc->reg[proc->op->param[2] - 1] ? 0 : 1);
	if (vm->verbosity & V_OP)
		show_gates(proc, param);
}
