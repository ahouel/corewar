/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:13:38 by lchety            #+#    #+#             */
/*   Updated: 2017/11/16 17:12:59 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	show_mem(t_vm *vm)
{
	printf(">>>>>>>>SHOW MEM<<<<<<<<\n");
	printf("Cycle : %d\n", vm->cycle);
	int i;
	i = 0;

	while (i < MEM_SIZE)
	{
		printf("%02x ", vm->ram[i].mem);
		if (i / 64 != (i + 1) / 64)
			printf("\n");
		i++;
	}
	printf("\n\n");
}

void	show_proc_nb(t_vm *vm)
{
	t_pcb *tmp;
	int i;

	i = 0;
	tmp = vm->proc;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	// printf("NB_PROC => %d\n", i);
}

void	debug_display_proc(t_vm *vm)
{
	t_pcb *tmp;
	int i;

	i = 0;
	tmp = vm->proc;
	while (tmp)
	{
		move (24 + i, 198);
		printw("Proc n:%d on:%d num:%d pc:%d live:%d", i, tmp->state, tmp->uid, tmp->pc, tmp->last_live);
		tmp = tmp->next;
		i++;
	}


}

static void	display_args(t_vm *vm, t_pcb *proc, int n)
{
	if (proc->op->ar_typ[n] == REG_CODE)
		printf("r");
	printf("%d", proc->op->ar[n]);
}

void	show_operations(t_vm *vm, t_pcb *proc)
{
	int	nb_arg;
	int i;

	i = 0;
	nb_arg = op_tab[proc->op->code - 1].nb_arg;
	printf("P%5d | %s", proc->uid + 1, op_tab[proc->op->code - 1].inst);
	while (i < nb_arg)
	{
		printf(" ");
		display_args(vm, proc, i);
		i++;
	}
}

void	show_pc_move(t_vm *vm, t_pcb *proc)
{
	int	i;
	int	move_size;

	i = 0;
	move_size = proc->pc - proc->last_pc;
	if (move_size > 1)
	{
		printf("ADV %d (0x%04x -> 0x%04x)", move_size, proc->last_pc, proc->pc);
		while (i < move_size)
		{
			// printf(">> %d \n", i);
			printf(" %02x", (unsigned char)vm->ram[(proc->last_pc + i) % MEM_SIZE].mem);
			i++;
		}
		printf("\n");
		// printf("\n");
	}
}
