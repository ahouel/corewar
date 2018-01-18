/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:03:17 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/17 19:07:16 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Prend la valeur du registre passe en parametre modulo 256,
**	si elle est non nulle la stock dans l'aff du joueur
*/

void	aff(t_vm *vm, t_pcb *proc)
{
	char	c;

	c = (proc->reg[proc->op->param[0] - 1] % 256);
	proc->aff = c;
	if (vm->aff)
		ft_printf("Processus %d owned by player %d is doing an aff : %c\n",
				proc->pid, proc->uid, c);
	proc->carry = (c ? 0 : 1);
}
