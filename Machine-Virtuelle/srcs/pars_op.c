/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:22:35 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:25:01 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_op(t_op *op)
{
	op->ar[0] = 0;
	op->ar[1] = 0;
	op->ar[2] = 0;
	op->ar_typ[0] = 0;
	op->ar_typ[1] = 0;
	op->ar_typ[2] = 0;
}

t_op		*create_op(t_vm *vm, t_pcb *proc, char data)
{
	int		i;
	t_op	*op;

	i = 0;
	op = NULL;
	if (!is_opcode(data))
		return (NULL);
	if (!(op = (t_op*)ft_memalloc(sizeof(t_op))))
		error("error : malloc\n");
	init_op(op);
	op->code = data;
	op->loadtime = op_tab[data - 1].loadtime - 1;
	op->pos_opcode = proc->pc;
	// printf("create_op  name : %s   delay : %d\n", op_tab[data - 1].name, op_tab[data - 1].loadtime);
	return (op);
}

void	fill_cur_op(t_vm *vm, t_pcb *proc)
{
	int i;
	t_optab *optab_ref;

	i = 0;

	optab_ref = &op_tab[proc->op->code - 1];
	if (optab_ref->need_ocp)
	{
		get_ocp(vm, proc);
		while (i < op_tab[proc->op->code - 1].nb_arg)
		{
			find_args(vm, proc, i);
			i++;
		}
	}
	else
	{
		get_dir(vm, proc, 0);
	}
	proc->pc++;
}
