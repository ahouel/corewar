/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:22:23 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:11:48 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	or(t_vm *vm, t_pcb *proc)
{
	unsigned int	ar1;
	unsigned int	ar2;

	if (proc->op->ar_typ[0] == T_REG)
		ar1 = proc->reg[proc->op->ar[0]];
	else
		ar1 = proc->op->ar[0];
	if (proc->op->ar_typ[1] == T_REG)
		ar2 = proc->reg[proc->op->ar[1]];
	else
		ar2 = proc->op->ar[1];
 	proc->reg[proc->op->ar[2]] = ar1 | ar2;
 	proc->carry = ((ar1 | ar2) == 0) ? 1 : 0;
}
