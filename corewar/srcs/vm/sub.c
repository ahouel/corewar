/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlambert <mlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:08:30 by mlambert          #+#    #+#             */
/*   Updated: 2017/11/09 10:21:29 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sub(t_vm *vm, t_proc *proc)
{
	int	n;

	n = proc->reg[proc->op->ar[0]] - proc->reg[proc->op->ar[1]];
	if (proc->op->ar[2] < 0 || proc->op->ar[2] > 17) // temp fix
		return ;
	proc->reg[proc->op->ar[2]] = n;
	proc->carry = (n == 0) ? 1 : 0;
}
