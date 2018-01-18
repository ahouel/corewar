/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_processus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:23:51 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/18 15:37:24 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Verifie si les registres appeles sont valides ou non
*/

static int	valid_regs(t_pcb *proc)
{
	int	i;

	i = -1;
	while (++i < 3)
		if (proc->op->param_type[i] == REG_CODE)
			if (proc->op->param[i] > REG_NUMBER || proc->op->param[i] < 1)
				return (0);
	return (1);
}

/*
**	Return le num du tableau op_tab[num] correspondant a l'op de data
*/

static int	which_op(unsigned char data)
{
	int	i;

	i = -1;
	while (++i < NBR_OP)
	{
		if (g_op_tab[i].code == (int)data)
			return (i);
	}
	return (-1);
}

/*
**	Creation d'un op vierge, copie sur le correspondant dans op.c
*/

static t_op	*new_op(t_vm *vm, char data)
{
	int		i;
	t_op	*op;

	i = 0;
	op = NULL;
	if (!(op = (t_op*)ft_memalloc(sizeof(t_op))))
		error(vm, "malloc failed");
	ft_memcpy(op, &g_op_tab[which_op(data)], sizeof(t_op));
	op->loadtime--;
	return (op);
}

/*
**	Execute l'op du processus
*/

static void	exe_processus(t_vm *vm, t_pcb *proc)
{
	int	last_pc;

	last_pc = proc->pc;
	load_op(vm, proc);
	if (proc->op->func != NULL && valid_regs(proc))
	{
		if (vm->verbosity & V_OP)
			ft_printf("P    %d | %s ", proc->pid, proc->op->label);
		proc->op->func(vm, proc);
	}
	if (vm->verbosity & V_PC && (proc->op->code != 9 || !proc->carry))
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x)",
				proc->pc - last_pc, last_pc, proc->pc);
		while (last_pc < proc->pc)
		{
			ft_printf(" %02x", vm->ram[last_pc % MEM_SIZE].mem);
			++last_pc;
		}
		ft_printf("\n");
	}
	proc->op ? free(proc->op) : 0;
	proc->op = NULL;
}

/*
**	Avance le processus d'une case s'il n'a pas d'op.
**	Autrement l'execute en prenant en compte son temps de load
*/

void		move_processus(t_vm *vm, t_pcb *proc)
{
	if (!proc->op)
	{
		if (which_op(vm->ram[proc->pc % MEM_SIZE].mem) > -1)
			proc->op = new_op(vm, vm->ram[proc->pc % MEM_SIZE].mem);
		else
			proc->pc = (proc->pc + 1) % MEM_SIZE;
	}
	else
	{
		proc->op->loadtime--;
		if (proc->op->loadtime < 1)
			exe_processus(vm, proc);
	}
	proc->pc %= MEM_SIZE;
}
