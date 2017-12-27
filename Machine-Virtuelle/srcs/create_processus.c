/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:59:54 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/15 16:49:02 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Creation d'un processus pour le joueur <num>
**	pid = process identifier
*/

t_pcb		*create_processus(t_vm *vm, int num)
{
	t_pcb	*new;

	new = NULL;
	if (!(new = (t_pcb*)ft_memalloc(sizeof(t_pcb))))
		error(vm, "malloc failed");
	++vm->nb_proc;
	new->pid = vm->nb_proc;
	new->uid = num + 1;
	new->pc = (MEM_SIZE / vm->nb_player) * num;
	new->op = NULL;
	ft_bzero(new->reg, sizeof(int) * (REG_NUMBER + 1));
	new->carry = 0;
	new->last_live = 0;
	new->reg[0] = -(num + 1);
	return (new);
}
