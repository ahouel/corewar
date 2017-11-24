/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:21:24 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/24 16:03:06 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		count_pcb(t_vm *vm)
{
	int i;
	t_pcb	*proc;

	i = 0;
	proc = vm->proc;
	while (proc)
	{
		if (proc->state == 'R')
			i++;
		proc = proc->next;
	}
	return (i);
}

int		modulo(int a, int b)
{
	if (a % b >= 0)
		return (a % b);
	else
		return ((a % b) + b);
	// return (a % b) >= 0 ? (a % b) : (a % b) + b;
}

static int	get_winner(t_vm *vm)
{
	int i;
	int best;


	i = -1;
	best = 0;
	while (++i < vm->nb_player)
		if (vm->player[i].last_live < vm->player[best].last_live)
			best = i;
	return (best);
}

static void	init_vm(t_vm *vm)
{
	vm->nb_player = 0;
//	vm->lives_in_cycle = 0;
	vm->ctd = CYCLE_TO_DIE;
	vm->cycle = 0;
	vm->proc = NULL;
	vm->last_one = NULL;
	vm->pause = 1;
	vm->ncurses = 0;
	vm->delay = NCURSES_DELAY;
	vm->ctd_check = 0;
	vm->next_ctd = CYCLE_TO_DIE;
	vm->dump = -1;
	vm->debug = -1;
	ft_bzero(&vm->ram, sizeof(t_mem) * MEM_SIZE);
}

int		main(int argc, char **argv)
{
	int			win;
	t_vm		vm;
	WINDOW		*w;

	init_vm(&vm);
	if(!check_arg(&vm, argc, argv))
		error("Error : no player\n");
	if (vm.ncurses)
		init_ncurses(&w);
	initialisation(&vm);
	if (vm.debug == 0)
		show_players(&vm);
	if (vm.debug == 1)
		print_ram(&vm);
	if (vm.debug == 2)
		show_processus(&vm);
	//ft_printf("=======FIGHT=======\n");
	//ft_printf("verbo : %d", vm.verbosity);
	exe(&vm);
	if (vm.ncurses)
		endwin();
	win = get_winner(&vm);
	ft_printf("Contestant %d, \"%s\", has won !\n", win + 1, vm.player[win].name);
	return (0);
}
