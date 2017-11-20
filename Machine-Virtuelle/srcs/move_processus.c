/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_processus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:23:51 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/20 16:14:29 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Check si data est un code op
*/

static char	is_opcode(char data)
{
	int i;

	i = -1;
	while (++i < NBR_OP)
	{
		if ((char)op_tab[i].code == data)
			return (data);
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
	if (!is_opcode(data))
		return (NULL);
	if (!(op = (t_op*)ft_memalloc(sizeof(t_op))))
		error("error : malloc\n");
	ft_memcpy(op, &op_tab[data], sizeof(t_op));
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
		ft_printf("%{BLUE}02x\n", proc->pc);
		}
		else
		{
			proc->pc = (proc->pc + 1) % MEM_SIZE;
		}
	}
	else
	{
		proc->op->loadtime--;
		if (proc->op->loadtime < 1)
		{
			load_op(vm, proc);
			if (op_tab[proc->op->code - 1].func != NULL)
			{
				op_tab[proc->op->code - 1].func(vm, proc);
			}
			proc->op = NULL;
		}
	}
}
