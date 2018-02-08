/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 17:54:45 by ahouel            #+#    #+#             */
/*   Updated: 2018/02/08 18:01:31 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	delete_aff(int p, t_vm *vm)
{
	int		i;

	i = 2;
	attron(COLOR_PAIR(99));
	while (++i < 248)
		mvprintw(65 + p * 2, i, "*");
	vm->aff_ncurses.in[p - 1] = 0;
}

void		print_aff(t_vm *vm)
{
	t_pcb	*tmp;
	int		i;

	tmp = vm->proc_lst;
	while (tmp)
	{
		if (tmp->aff > 0)
		{
			attron(COLOR_PAIR(vm->player[tmp->uid - 1].id_color));
			mvprintw(65 + tmp->uid * 2, vm->aff_ncurses.in[tmp->uid - 1]++
				+ 3, "%c", tmp->aff);
			vm->aff_ncurses.end[tmp->uid - 1] = AFF_DELAY;
			tmp->aff = -1;
		}
		tmp = tmp->next;
	}
	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->aff_ncurses.end[i])
			vm->aff_ncurses.end[i]--;
	i = -1;
	while (++i < MAX_PLAYERS)
		if (!vm->aff_ncurses.end[i] || vm->aff_ncurses.in[i] > 245)
			delete_aff(i + 1, vm);
}
