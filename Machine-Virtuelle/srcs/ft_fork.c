/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:19:23 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/15 17:44:47 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Montre l'address fork avec -v 4
*/

static void	show_fork(t_pcb *proc, t_pcb *new)
{
	ft_printf("%d (%d)\n", proc->op->param[0], new->pc);
}

/*
**	Genere un nouveau processus a l'adresse passée en parametre
**	par copie du processus appelant. Le nouveau processus garde
**	donc l'etat de tout les registres et du carry,
**	seul le PC differe ( sauf dans le cas d'un fork %0 ).
*/

void		ft_fork(t_vm *vm, t_pcb *proc)
{
	t_pcb	*new;

	new = create_processus(vm, 0);
	new = (t_pcb*)ft_memcpy(new, proc, sizeof(t_pcb));
	new->pid = vm->nb_proc;
	new->uid = proc->uid;
	new->pc = get_address(vm, proc, proc->op->param[0]);
	new->op = NULL;
	add_processus(vm, new);
	if (vm->verbosity & V_OP)
		show_fork(proc, new);
}
