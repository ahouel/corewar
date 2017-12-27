/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:58:44 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/21 17:00:01 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Initiaisation de la structure environnement de la vm
*/

void	init_vm(t_vm *vm)
{
	int	i;

	i = -1;
	ft_bzero(vm, sizeof(t_vm));
	vm->delay = NCURSES_DELAY;
	vm->ctd = CYCLE_TO_DIE;
	vm->next_ctd = CYCLE_TO_DIE;
	vm->dump = -1;
	vm->debug = -1;
	ft_bzero(&vm->ram, sizeof(t_mem) * MEM_SIZE);
	while (++i < MAX_PLAYERS)
		vm->player[i].id_color = i + 5;
}
