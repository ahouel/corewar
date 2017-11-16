/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:20:37 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:10:58 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void registre_cpy(t_pcb *proc, t_proc *new)
{
	int i;

	i = 0;
	while (i <= REG_NUMBER)
	{
		new->reg[i] = proc->reg[i];
		i++;
	}

}

static void	clone_proc(t_pcb *proc, t_proc *new)
{
	registre_cpy(proc, new);
	new->carry = proc->carry;
	new->last_live = proc->last_live;
}

void	ft_lfork(t_vm *vm, t_pcb *proc)
{
	t_proc	*new;
	new = create_process(vm, proc->num);

	new->pc = modulo(proc->op->pos_opcode + proc->op->ar[0], MEM_SIZE);
	new->last_pc = new->pc;
	clone_proc(proc, new);
	add_process(vm, new);

	if (0x4 & vm->verbosity)
	{
		show_operations(vm, proc);
		printf(" (%d)\n", new->pc);
	}
}
