/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbradel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:07:58 by gbradel           #+#    #+#             */
/*   Updated: 2018/01/15 17:07:01 by ahouel           ###   ########.fr       */
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

void	init_ncurses(t_vm *vm, WINDOW **w)
{
	*w = initscr();
	if (has_colors() == FALSE)
	{
		ft_printf("Your terminal does not support colors.\n");
		endwin();
		exit(1);
	}
	start_color(); // start color
	cbreak(); //getch() no block
	curs_set(0);
	nodelay(*w, TRUE);
	colors_init(vm);
	basic_print(0);
	basic_print_two(0, vm);
}
