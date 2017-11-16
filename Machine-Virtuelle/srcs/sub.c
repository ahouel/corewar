/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:24:18 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:14:02 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	sub(t_vm *vm, t_pcb *proc)
{
	int	n;

	n = proc->reg[proc->op->ar[0]] - proc->reg[proc->op->ar[1]];
	if (proc->op->ar[2] < 0 || proc->op->ar[2] > 17) // temp fix
		return ;
	proc->reg[proc->op->ar[2]] = n;
	proc->carry = (n == 0) ? 1 : 0;
}
