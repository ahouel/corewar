/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:13:38 by lchety            #+#    #+#             */
/*   Updated: 2017/11/24 16:03:05 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	show_players(t_vm *vm)
{
	int	i;
	t_player	*p;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		p = &vm->player[i];
		ft_printf("Player[%d]\nname : %s\ncomment : %s\nactive : %d\nlife_signal : %d\nfile_name : %s\n", i, p->name, p->comment, p->active, p->life_signal, p->file_name);
	}
}

void	show_processus(t_vm *vm)
{
	t_pcb	*proc;

	proc = vm->proc;
	while (proc)
	{
		ft_printf("pid : %d\nuid : %d\nlast_pc : %d\npc : %d\nstate : %c\ncarry : %c\nlast live : %d\n", proc->pid, proc->uid, proc->last_pc, proc->pc, proc->pc, proc->state, proc->carry, proc->last_live);
	proc = proc->next;
	}
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
	if (proc->op->ocp[n] == REG_CODE)
		printf("r");
	printf("%d", proc->op->ocp[n]);
}

void	show_ops(t_vm *vm)
{
	t_pcb	*proc;
	t_op	*op;


	proc = vm->proc;
	while (proc)
	{
		op = proc->op;
		if (op)
			ft_printf("inst : %s, ocp[0] : %d, [1] : %d, [2] : %d, code : %d, name : %s\n", op->inst, op->ocp[0], op->ocp[1], op->ocp[2], op->code, op->name);
		proc = proc->next;
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
