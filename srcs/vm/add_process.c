/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:37:59 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/10 15:43:07 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add_process(t_vm *vm, t_proc *proc)
{
	t_proc	*tmp;

	if (vm->proc)
	{
		proc->next = vm->proc;
		vm->proc = proc;
	}
	else
	{
		vm->proc = proc;
	}
}
