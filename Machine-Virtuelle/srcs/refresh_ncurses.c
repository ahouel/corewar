/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_ncurses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbradel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:15:14 by gbradel           #+#    #+#             */
/*   Updated: 2018/01/12 17:15:16 by gbradel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	refresh_all(t_vm *vm)
{
	t_pcb	*tmp;

	tmp = vm->proc_lst;
	attron(COLOR_PAIR(40));
	mvprintw(7, 216, "%d", vm->cycle);
	mvprintw(12, 212, "%d", vm->nb_proc);
	mvprintw(5, 220, "%d", vm->delay);
	mvprintw(36, 215, "%d", vm->ctd);
	mvprintw(39, 214, "%d", CYCLE_DELTA);
	mvprintw(42, 211, "%d", NBR_LIVE);
	mvprintw(45, 212, "%d", MAX_CHECKS);
	while (tmp)
	{
		attron(COLOR_PAIR(vm->player[tmp->uid - 1].id_color + 5));
		mvprintw((1 + tmp->pc / 64), (3 + (tmp->pc % 64) * 3), "%02x",
			(unsigned char)vm->ram[tmp->pc].mem);
		attroff(COLOR_PAIR(vm->player[tmp->uid - 1].id_color + 5));
		tmp = tmp->next;
	}
}
