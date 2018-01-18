/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:21:33 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/15 17:07:02 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_player(t_vm *vm)
{
	int		i;
	int		j;

	i = 0;
	j = 16;
	while (MAX_PLAYERS >= ++i)
	{
		while (MAX_PLAYERS >= i && !vm->player[i - 1].name)
			++i;
		if (MAX_PLAYERS < i)
			return ;
		attron(COLOR_PAIR(40));
		mvprintw(j, 200, "Player -%d : ", i);
		mvprintw(++j, 201, "last live : ");
		mvprintw(++j, 201, "live in current period : ");
		attroff(COLOR_PAIR(40));
		attron(COLOR_PAIR(vm->player[i - 1].id_color));
		mvprintw(j - 2, 212, "%s", vm->player[i - 1].name);
		mvprintw(j - 1, 213, "%d", vm->player[i - 1].last_live);
		mvprintw(j, 226, "%d", vm->player[i - 1].lives_count);
		attroff(COLOR_PAIR(vm->player[i - 1].id_color));
		j += 3;
	}
}

static void	wprint_ram(t_vm *vm)
{
	int		i;
	int		j;

	i = -1;
	while (++i < MEM_SIZE)
	{
		j = 0;
		while (vm->ram[i].num != j)
			j++;
		if (j == 0)
			attron(COLOR_PAIR(20));
		else
			attron(COLOR_PAIR(vm->player[j - 1].id_color));
		mvprintw((1 + i / 64), (3 + (i % 64) * 3), "%02x",
			vm->ram[i].mem);
		if (j == 0)
			attroff(COLOR_PAIR(20));
		else
			attroff(COLOR_PAIR(vm->player[j - 1].id_color));
	}
}

void		call_ncurses(t_vm *vm)
{
	print_player(vm);
	wprint_ram(vm);
	refresh_all(vm);
	move(0, 0);
	refresh();
	usleep(vm->delay);
}
