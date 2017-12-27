/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_processus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:17:29 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/14 12:48:18 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Ajoute un processus proc a la list chainee dans la vm
*/

void	add_processus(t_vm *vm, t_pcb *proc)
{
	if (vm->proc_lst)
	{
		proc->next = vm->proc_lst;
		vm->proc_lst = proc;
	}
	else
	{
		vm->proc_lst = proc;
	}
}
