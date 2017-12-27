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

static void	colors_init(t_vm *vm)
{
	/*init_color(35, 350, 350, 350);//basic grey
	init_color(40, 1000, 1000, 1000);//basic white
	init_pair(15, 35, COLOR_BLACK);//basic
	init_pair(40, COLOR_BLACK, 40);//basic white on black
	init_pair(41, 35, 35);//grey back
	init_pair(20, COLOR_GREEN, COLOR_BLACK);//player_1
	init_color(36, 150, 1000, 150);//fluo_green
	init_color(38, 500, 1000, 500);//blingbling_green
	init_pair(21, COLOR_GREEN, 36);//player_1_highlight
	init_pair(24, 38, COLOR_BLACK);//player_1_blingbling
	init_pair(22, COLOR_BLUE, COLOR_BLACK);//player_2
	init_color(COLOR_BLUE, 200, 200, 800);//blue change
	init_color(37, 400, 400, 1000);//fluo_blue
	init_pair(23, COLOR_BLUE, 37);//player_2_highlight
	init_pair(25, 37, COLOR_BLACK);//player_2_blingbling
	init_pair(26, COLOR_GREEN, COLOR_RED);//life highlight*/
	init_color(35, 350, 350, 350);//basic grey
	init_color(40, 1000, 1000, 1000);//basic white
	init_color(50, 102, 1000, 1000); // fluo blue
	init_color(60, 1000, 302, 824); // fluo pink
	init_color(70, 102, 1000, 102); // fluo green
	init_color(80, 1000, 1000, 102); // fluo yellow
	init_color(55, 51, 500, 500);
	init_color(65, 500, 151, 412);
	init_color(75, 51, 500, 51);
	init_color(85, 500, 500, 51);
	init_pair(5, 50, COLOR_BLACK); // fluo blue on black
	init_pair(6, 60, COLOR_BLACK); // fluo pink on black
	init_pair(7, 70, COLOR_BLACK); // fluo green on black
	init_pair(8, 80, COLOR_BLACK); // fluo yellow on black
	init_pair(10, 50, 55); // fluo blue on black for ps
	init_pair(11, 60, 65); // fluo pink on black for ps
	init_pair(12, 70, 75); // fluo green on black for ps
	init_pair(13, 80, 85); // fluo yellow on black for ps
	vm->player[0].id_color = 5;
	vm->player[1].id_color = 6;
	vm->player[2].id_color = 7;
	vm->player[3].id_color = 8;
	init_pair(42, 35, 35);
	init_pair(20, 35, COLOR_BLACK);
	init_pair(30, COLOR_RED, COLOR_BLACK);
	init_pair(40, 40, COLOR_BLACK);
}

/*static int is_pc(t_vm *vm, int i)
{
	int	j;

	j = -1;
	while (++j < NBR_OP + 1)
	{
		if ((int)vm->ram[i].mem == op_tab[j].code)
			return (1);
	}
	return (0);
}*/

/*static void	ram_init(t_vm *vm)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		attron(COLOR_PAIR(15));
		if ((is_pc(vm, i)))
		{
			if (vm->ram[i].num == 1)
				attron(COLOR_PAIR(21));
			else if (vm->ram[i].num == 2)
				attron(COLOR_PAIR(23));
			attron(A_STANDOUT);
		}
		else if (vm->ram[i].num == 1)
		{
			attron(COLOR_PAIR(20));
		}
		else if (vm->ram[i].num == 2)
		{
			attron(COLOR_PAIR(22));
		}
		if (vm->ram[i].flash)
		{
			attron(A_BOLD);
			if (vm->ram[i].num == 1)
				attron(COLOR_PAIR(24));
			if (vm->ram[i].num == 2)
				attron(COLOR_PAIR(25));
			vm->ram[i].flash--;
		}
//		if (vm->ram[i].live)
//		{
//			attron(COLOR_PAIR(26));
//			vm->ram[i].live--;
//		}
		mvprintw((3 + i / 64), (3 + (i % 64) * 3), "%02x", (unsigned char)vm->ram[i].mem);
		attroff(A_STANDOUT);
		attroff(A_BOLD);
		attroff(COLOR_PAIR(35));
	}
}*/

/*void	call_ncurses(t_vm *vm)
{
	int i;
	int	j;
	int ret;

	i = -1;
	ret = 0;
	colors_init();
	ram_init(vm);
	attron(COLOR_PAIR(41));
	attron(A_INVIS);
	while (++i < MEM_SIZE / 64 + 6)
	{
		j = -1;
		while (++j < 3 * (MEM_SIZE / 64) + 50)
		{
			if (i == 0 || j == 0 || i == MEM_SIZE / 64 + 5
					|| j == 3 * (MEM_SIZE / 64) + 4 ||
					j == 3 * (MEM_SIZE / 64) + 49)
				mvprintw(i, j, "*");
		}
	}
	attroff(COLOR_PAIR(41));
	attroff(A_INVIS);
	attron(A_STANDOUT);
	attron(COLOR_PAIR(40));
	attron(A_BOLD);
	mvprintw(32, 3 * (MEM_SIZE / 64) + 6, "%d <= pause", vm->pause);
	if (!vm->pause)
		mvprintw(2, 3 * (MEM_SIZE / 64) + 6, "** PAUSED **");
	if (vm->pause)
		mvprintw(2, 3 * (MEM_SIZE / 64) + 6, "** RUNNING **");
	mvprintw(5, 3 * (MEM_SIZE / 64) + 6, "Delay : %d", vm->delay);
	mvprintw(10, 3 * (MEM_SIZE / 64) + 6, "Cycles : %d", vm->cycle);
//`	mvprintw(14, 3 * (MEM_SIZE / 64) + 6, "Proc Nb : %d", count_proc(vm));
	mvprintw(22, 3 * (MEM_SIZE / 64) + 6, "CYCLE_TO_DIE : %d", vm->ctd);
	mvprintw(24, 3 * (MEM_SIZE / 64) + 6, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvprintw(26, 3 * (MEM_SIZE / 64) + 6, "NBR_LIVE : %d", NBR_LIVE);
	mvprintw(28, 3 * (MEM_SIZE / 64) + 6, "MAX_CHECKS : %d", MAX_CHECKS);
	mvprintw(30, 3 * (MEM_SIZE / 64) + 6, "Live P1 : %08d", vm->player[1].lives_count);
	printw("%i", MEM_SIZE);
	attroff(COLOR_PAIR(40));
	//attron(A_BOLD);
	attroff(A_BOLD);
	attroff(A_STANDOUT);
	// debug_display_proc(vm);

	refresh();
}*/

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

void	basic_print_two(int i, t_vm *vm)
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

void	print_player(t_vm *vm)
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

void	wprint_ram(t_vm *vm)
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
		mvprintw((1 + i / 64), (3 + (i % 64) * 3), "%02x", (unsigned char)vm->ram[i].mem);
		if (j == 0)
			attroff(COLOR_PAIR(20));
		else
			attroff(COLOR_PAIR(vm->player[j - 1].id_color));
	}
}

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
		mvprintw((1 + tmp->pc / 64), (3 + (tmp->pc % 64) * 3), "%02x", (unsigned char)vm->ram[tmp->pc].mem);
		attroff(COLOR_PAIR(vm->player[tmp->uid - 1].id_color + 5));
		tmp = tmp->next;
	}
}

void	live_stats(t_vm *vm)
{
	int		total;
	int		i;
	int		tmp;

	total = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
		total += vm->player[i].lives_count;
	/*if (i == 0)
		ft_transfert_stats();*/
	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->player[i].name)
		{
			tmp = (vm->player[i].lives_count / total) * 100 * 41;
			if (tmp % 100 > 50)
				tmp += 50;
			
		}
}

void	call_ncurses(t_vm *vm)
{
	colors_init(vm); // une seule fois
	basic_print(0); // une seule fois
	basic_print_two(0, vm); // une seule fois
	print_player(vm); // tout les tours
	wprint_ram(vm); // tout les tours
	refresh_all(vm); // tout les tours
	live_stats(vm); // tout les tours
	refresh();
}

void	init_ncurses(WINDOW **w)
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
}
