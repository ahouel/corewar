/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_processus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:23:51 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/27 14:00:10 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Check si data est un code op
*/

static int	is_opcode(unsigned char data)
{
	int i;

	i = -1;
	while (++i < NBR_OP)
	{
		if (op_tab[i].code == (int)data)
			return (1);
	}
	return (0);
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
		if (op_tab[i].code == (int)data)
			return (i);
	}
	return (0);
}

/*
**	Creation d'un op vierge, copie sur le correspondant dans op.c
*/

static t_op	*new_op(t_vm *vm, t_pcb *proc, char data)
{
	int		i;
	t_op	*op;

	i = 0;
	op = NULL;
	if (!(op = (t_op*)ft_memalloc(sizeof(t_op))))
		error("error : malloc\n");
	ft_memcpy(op, &op_tab[which_op(data)], sizeof(t_op));
	return (op);
}

/*
**	Avance le processus d'une case s'il n'a pas d'op.
**	Autrement l'execute en prenant en compte son temps de load
*/

void		move_processus(t_vm *vm, t_pcb *proc)
{
	if(!proc->op)
	{
		if (is_opcode(vm->ram[proc->pc % MEM_SIZE].mem))
		{
			proc->op = new_op(vm, proc, vm->ram[proc->pc % MEM_SIZE].mem);
		}
		proc->pc = (proc->pc + 1) % MEM_SIZE;
	}
	else
	{
		proc->op->loadtime--;
		if (proc->op->loadtime < 1)
		{
			load_op(vm, proc);
			if (proc->op->func != NULL)
			{
				proc->op->func(vm, proc);
			}
			proc->op = NULL;
		}
	}
}
