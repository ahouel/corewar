/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_address.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 16:12:02 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/15 17:06:52 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Prend la reele addresse a chercher dans la ram,
**	a partir de l'adresse visee addr
**	la % si l'adressage est restreint et ajoute le pc de l op precedente
*/

int	get_address(t_vm *vm, t_pcb *proc, int addr)
{
	int	i;

	i = 3;
	proc->op->addr_rest ? (addr %= IDX_MOD) : 0;
	addr += (proc->pc - (proc->op->has_ocp ? 2 : 1));
	while (--i > -1)
	{
		if (proc->op->param_type[i] == REG_CODE)
			addr--;
		if (proc->op->param_type[i] == IND_CODE)
			addr -= 2;
		if (proc->op->param_type[i] == DIR_CODE)
			addr -= (proc->op->nb_byte ? 2 : 4);
	}
	return (addr % MEM_SIZE);
}
