/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbradel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:07:58 by gbradel           #+#    #+#             */
/*   Updated: 2018/01/24 16:56:45 by ahouel           ###   ########.fr       */
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
	while (++i < 83)
	{
		mvprintw(i, 0, "*");
		mvprintw(i, 1, "*");
		mvprintw(i, 249, "*");
		mvprintw(i, 248, "*");
	}
	i = 195;
	while (++i < 249)
	{
		mvprintw(2, i, "*");
		mvprintw(48, i, "*");
	}
	attroff(COLOR_PAIR(42));
}

static void	basic_print_two(void)
{
	attron(COLOR_PAIR(40));
	mvprintw(5, 200, "Cycle max /second : ");
	mvprintw(7, 200, "Current cycle : ");
	mvprintw(12, 200, "Processes : ");
	mvprintw(50, 204, "live breakdown for current period :");
	mvprintw(53, 198, "||");
	mvprintw(55, 198, "||");
	mvprintw(53, 244, "||");
	mvprintw(55, 244, "||");
	mvprintw(54, 198, "||||||||||||||||||||||||||||||||||||||||||||||||");
	mvprintw(58, 206, "live breakdown for last period :");
	mvprintw(61, 198, "||");
	mvprintw(63, 198, "||");
	mvprintw(61, 244, "||");
	mvprintw(63, 244, "||");
	mvprintw(62, 198, "||||||||||||||||||||||||||||||||||||||||||||||||");
	mvprintw(36, 200, "CYCLE_TO_DIE : ");
	mvprintw(39, 200, "CYCLE_DELTA : ");
	mvprintw(42, 200, "NBR_LIVE : ");
	mvprintw(45, 200, "MAX_CHECK : ");
	attron(COLOR_PAIR(30));
	mvprintw(1, 216, "~ ~ PAUSED ~ ~");
	attron(COLOR_PAIR(20));
	mvprintw(65, 123, " CHAT ");
	mvprintw(48, 217, " live stats ");
}

static void	basic_print_three(void)
{
	int		i;

	attron(COLOR_PAIR(42));
	i = -1;
	while (++i < 65)
	{
		mvprintw(i, 195, "*");
		mvprintw(i, 196, "*");
	}
}

void		init_ncurses(void)
{
	void	*w;

	w = initscr();
	if (has_colors() == FALSE)
	{
		ft_printf("Your terminal does not support colors.\n");
		endwin();
		exit(1);
	}
	start_color();
	cbreak();
	curs_set(0);
	noecho();
	nodelay(w, TRUE);
	ncurses_colors_init('1');
	basic_print(0);
	basic_print_two();
	basic_print_three();
}
