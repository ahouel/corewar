/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:13:38 by lchety            #+#    #+#             */
/*   Updated: 2017/12/15 16:59:58 by ahouel           ###   ########.fr       */
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
		ft_printf("Player[%d]\nname : %s\ncomment : %s\nactive : %d\nlives_count : %d\nfile_name : %s\n",
				i, p->name, p->comment, p->active, p->lives_count, p->file_name);
	}
}

void	show_processus(t_vm *vm)
{
	t_pcb	*proc;
	int i;

	i = 0;
	proc = vm->proc_lst;
	ft_printf("%{CYAN}s\n", "APPEL SHOW PROC");
	while (proc)
	{
		ft_printf("%{RED}s %{BLUE}d\n", "proc n :", ++i);
		ft_printf("pid : %d\nuid : %d\npc : %d\ncarry : %d\n", proc->pid, proc->uid, proc->pc, proc->carry);
	proc = proc->next;
	}
}

static void	display_args(t_vm *vm, t_pcb *proc, int n)
{
	if (proc->op->param[n] == REG_CODE)
		printf("r");
	printf("%d", proc->op->param[n]);
}

void	show_ops(t_vm *vm)
{
	t_pcb	*proc;
	t_op	*op;


	proc = vm->proc_lst;
	while (proc)
	{
		op = proc->op;
		ft_printf("proc %d pc : %d\t", proc->pid, proc->pc);
		if (op)
			ft_printf("inst : %s, ocp[0] : %d, [1] : %d, [2] : %d, code : %d, name : %s\n", op->label, op->param[0], op->param[1], op->param[2], op->code, op->name);
		proc = proc->next;
	}
}
