/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:21:33 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/15 16:31:27 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	basic_print(int i)
{
	attron(COLOR_PAIR(42));
	i = -1;
	while (++i < 250)
	{
		mvprintw(0, i, "*");
		mvprintw(83, i, "*");
		mvprintw(65, i, "*");
	}
	i = -1;
	while (++i < 84)
	{
		mvprintw(i, 0, "*");
		mvprintw(i, 1, "*");
		mvprintw(i, 249, "*");
		mvprintw(i, 248, "*");
		mvprintw(i, 195, "*");
		mvprintw(i, 196, "*");
	}
	i = 195;
	while (++i < 249)
	{
		mvprintw(2, i, "*");
		mvprintw(48, i, "*");
	}
	attroff(COLOR_PAIR(42));
}

static void	basic_print_two(int i, t_vm *vm)
{
	attron(COLOR_PAIR(40));
	mvprintw(5, 200, "Cycle max /second : ");
	mvprintw(7, 200, "Current cycle : ");
	mvprintw(12, 200, "Processes : ");
	mvprintw(50, 204, "live breakdown for current period :");
	mvprintw(53, 199, "||");
	mvprintw(55, 199, "||");
	mvprintw(53, 243, "||");
	mvprintw(55, 243, "||");
	mvprintw(54, 199, "||||||||||||||||||||||||||||||||||||||||||||||");
	mvprintw(58, 206, "live breakdown for last period :");
	mvprintw(61, 199, "||");
	mvprintw(63, 199, "||");
	mvprintw(61, 243, "||");
	mvprintw(63, 243, "||");
	mvprintw(62, 199, "||||||||||||||||||||||||||||||||||||||||||||||");
	mvprintw(36, 200, "CYCLE_TO_DIE : ");
	mvprintw(39, 200, "CYCLE_DELTA : ");
	mvprintw(42, 200, "NBR_LIVE : ");
	mvprintw(45, 200, "MAX_CHECK : ");
	attron(COLOR_PAIR(30));
	mvprintw(1, 216, "~ ~ PAUSED ~ ~");
	attron(COLOR_PAIR(20));
	mvprintw(65, 220, " CHAT ");
	mvprintw(48, 217, " live stats ");
}

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
			(unsigned char)vm->ram[i].mem);
		if (j == 0)
			attroff(COLOR_PAIR(20));
		else
			attroff(COLOR_PAIR(vm->player[j - 1].id_color));
	}
}

void		call_ncurses(t_vm *vm)
{
	static int	i = 0;
	
	if (!i)
	{
		colors_init(vm); // une seule fois
		basic_print(0); // une seule fois
		basic_print_two(0, vm); // une seule fois
		i++;
	}
	print_player(vm); // tout les tours
	wprint_ram(vm); // tout les tours
	refresh_all(vm); // tout les tours
	live_stats(vm); // tout les tours
	refresh();
}
