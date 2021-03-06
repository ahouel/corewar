/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:19:23 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/18 14:25:56 by ahouel           ###   ########.fr       */
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
**	seuls le PC et le pid different (sauf dans le cas d'un fork %0).
*/

void		ft_fork(t_vm *vm, t_pcb *proc)
{
	t_pcb	*new;
	t_pcb	*tmp;

	new = create_processus(vm, 0);
	tmp = new->next;
	new = (t_pcb*)ft_memcpy(new, proc, sizeof(t_pcb));
	new->next = tmp;
	new->pid = vm->next_pid;
	new->pc = get_address(proc, proc->op->param[0]);
	if (vm->verbosity & V_OP)
		show_fork(proc, new);
	while (new->pc < 0)
		new->pc += MEM_SIZE;
	new->op = NULL;
}
