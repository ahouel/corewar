/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:19:23 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/27 13:36:41 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_fork(t_vm *vm, t_pcb *proc)
{
	t_pcb	*new;

	new = create_processus(vm, proc->pid);
	new = (t_pcb*)ft_memcpy(new, proc, sizeof(t_pcb));
	new->pc = proc->pc + (proc->op->param[0] % IDX_MOD);
	while (new->pc < 0)
		new->pc += MEM_SIZE;
	new->pc %= MEM_SIZE;
	add_process(vm, new);
}
