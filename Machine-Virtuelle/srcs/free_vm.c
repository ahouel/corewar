/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:35:37 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/15 14:22:21 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Libere les strings aloues dans le tableau des joueurs
*/

static void	free_players(t_vm *vm)
{
	t_player	*player;
	int			i;

	i = -1;
	player = vm->player;
	while (++i < MAX_PLAYERS)
	{
		if (vm->player[i].comment)
		{
			free(vm->player[i].comment);
			vm->player[i].comment = NULL;
		}
		if (vm->player[i].name)
		{
			free(vm->player[i].name);
			vm->player[i].name = NULL;
		}
	}
}

/*
**	Libere toute memoire alouee
*/

void		free_vm(t_vm *vm)
{
	t_pcb		*proc;
	t_pcb		*tmp;

	if (!vm)
		return ;
	free_players(vm);
	proc = vm->proc_lst;
	while (proc)
	{
		tmp = proc;
		proc->op ? free(proc->op) : 0;
		proc = proc->next;
		free(tmp);
	}
	vm->proc_lst = NULL;
}
