/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:59:54 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/20 09:17:38 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	pid = process identifier
*/

static int	set_proc_pid(t_vm *vm)
{
	t_pcb *tmp;
	int nb;

	nb = 0;
	tmp = vm->proc;
	if (!tmp)
		return (nb);
	while (tmp)
	{
		tmp = tmp->next;
		nb++;
	}
	return (nb);
}

/*
**	Creation d'un processus pour le joueur <num>
*/


t_pcb	*create_processus(t_vm *vm, int num)
{
	t_pcb	*tmp;

	tmp = NULL;
	if(!(tmp = (t_pcb*)ft_memalloc(sizeof(t_pcb))))
		error("error : malloc\n");
	tmp->pid = set_proc_pid(vm);
	tmp->uid = num;
	tmp->reg[1] = num;
	tmp->pc = (MEM_SIZE / vm->nb_player) * num;
	tmp->last_pc = 0;
	tmp->op = NULL;
	ft_bzero(tmp->reg, sizeof(int) * (REG_NUMBER + 1));
	tmp->state = RUN;
	tmp->carry = 0;
	tmp->last_live = 0;
	return (tmp);
}
