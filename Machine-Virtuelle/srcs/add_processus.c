/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_processus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:17:29 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/15 12:12:40 by ahouel           ###   ########.fr       */
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
