/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:17:17 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:08:05 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add(t_vm *vm, t_pcb *proc)
{
	int	sum;

	if (proc->op->ar[0] < 1 || proc->op->ar[0] > 16)
		return ;
	if (proc->op->ar[1] < 1 || proc->op->ar[1] > 16)
		return ;
	if (proc->op->ar[2] < 1 || proc->op->ar[2] > 16)
		return ;
	sum = proc->reg[proc->op->ar[0]] + proc->reg[proc->op->ar[1]];
	proc->reg[proc->op->ar[2]] = sum;
	proc->carry = (sum == 0) ? 1 : 0;
}
