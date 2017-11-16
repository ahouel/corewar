/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:19:23 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:31:08 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	registre_cpy(t_pcb *proc, t_pcb *new)
{
	int i;

	i = 0;
	while (i <= REG_NUMBER)
	{
		new->reg[i] = proc->reg[i];
		i++;
	}
}

static void	clone_proc(t_pcb *proc, t_pcb *new)
{
	registre_cpy(proc, new);
	new->carry = proc->carry;
	new->last_live = proc->last_live;
}

void		ft_fork(t_vm *vm, t_pcb *proc)
{
	t_pcb	*new;

	new = NULL;
	if (!vm->ncurses && vm->debug)
		printf(">>>>>>>ENTER FORK<<<<<<<<<<  : Cycle > %d  : Pos > %d  : Proc > %d\n", vm->cycle, proc->op->pos_opcode, proc->pid);
	// if (vm->verbosity)
	new = create_processus(vm, proc->pid);
	new->pc = modulo(proc->op->pos_opcode + (proc->op->ar[0] % IDX_MOD), MEM_SIZE);
	new->last_pc = new->pc;
	clone_proc(proc, new);
	add_process(vm, new);
	if (0x4 & vm->verbosity)
	{
		show_operations(vm, proc);
		printf(" (%d)\n", new->pc);
	}
}
