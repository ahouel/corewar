/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_ncurses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbradel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:15:14 by gbradel           #+#    #+#             */
/*   Updated: 2018/01/29 17:51:49 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_live_store(t_vm *vm)
{
	t_pcb	*tmp;
	int		i;

	tmp = vm->proc_lst;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (vm->ram[i].store)
		{
			attron(COLOR_PAIR(vm->player[vm->ram[i].num - 1].id_color + 10));
			mvprintw((1 + i / 64), (3 + (i % 64) * 3), "%02x",
				vm->ram[i].mem);
			attroff(COLOR_PAIR(vm->player[tmp->uid - 1].id_color + 10));
			(vm->ram[i].store)--;
		}
		if (vm->ram[i].live)
		{
			attron(COLOR_PAIR(vm->player[vm->ram[i].num - 1].id_color + 20));
			mvprintw((1 + i / 64), (3 + (i % 64) * 3), "%02x",
				vm->ram[i].mem);
			attroff(COLOR_PAIR(vm->player[tmp->uid - 1].id_color + 10));
			(vm->ram[i].live)--;
		}
	}
}

static void	delete_aff(int p)
{
	int		i;

	i = 2;
	while (++i < 248)
	{
		mvprintw(65 + p * 2, i, "*");
	}
}

static void	print_aff(t_vm *vm)
{
	t_pcb	*tmp;
	int		i;

	tmp = vm->proc_lst;
	while (tmp)
	{
		if (tmp->aff)
		{
			attron(COLOR_PAIR(vm->player[tmp->uid - 1].id_color));
			mvprintw(65 + tmp->uid * 2, vm->aff_ncurses.in[tmp->uid]++ + 3, "%c", tmp->aff);
			vm->aff_ncurses.end[tmp->uid] = AFF_DELAY;
		}
		tmp = tmp->next;
	}
	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->aff_ncurses.end[i])
			vm->aff_ncurses.end[i]--;
	while (++i < MAX_PLAYERS)
		if (!vm->aff_ncurses.end[i])
			delete_aff(i);
}

void		refresh_all(t_vm *vm)
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
	attron(COLOR_PAIR(42));
	mvprintw(0, 0, "*");
	while (tmp)
	{
		attron(COLOR_PAIR(vm->player[tmp->uid - 1].id_color + 5));
		mvprintw((1 + tmp->pc / 64), (3 + (tmp->pc % 64) * 3), "%02x",
			vm->ram[tmp->pc].mem);
		attroff(COLOR_PAIR(vm->player[tmp->uid - 1].id_color + 5));
		tmp = tmp->next;
	}
	print_live_store(vm);
	print_aff(vm);
}
