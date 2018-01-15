/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:59:54 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/15 13:33:22 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Ajoute un processus proc a la list chainee dans la vm
*/

static void	add_processus(t_vm *vm, t_pcb *proc)
{
	if (vm->proc_lst)
	{
		proc->next = vm->proc_lst;
		vm->proc_lst = proc;
	}
	else
	{
		vm->proc_lst = proc;
	}
}

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
	++vm->next_pid;
	new->pid = vm->next_pid;
	new->uid = num + 1;
	if (vm->nb_player)
		new->pc = (MEM_SIZE / vm->nb_player) * num;
	new->op = NULL;
	ft_bzero(new->reg, sizeof(int) * (REG_NUMBER + 1));
	new->carry = 0;
	new->last_live = 0;
	new->reg[0] = -(num + 1);
	add_processus(vm, new);
	return (new);
}
