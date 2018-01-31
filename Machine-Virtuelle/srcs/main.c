/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:21:24 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/31 17:24:39 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Usage verbosity
*/

static void	usage_verbosity(void)
{
	ft_printf("\t\t %{CYAN}s\n", "- 1 : Show lives");
	ft_printf("\t\t %{CYAN}s\n", "- 2 : Show cycles");
	ft_printf("\t\t %{CYAN}s\n",
		"- 4 : Show operations (Params are NOT litteral ...)");
	ft_printf("\t\t %{CYAN}s\n", "- 8 : Show deaths");
	ft_printf("\t\t %{CYAN}s\n", "- 16 : Show PC movements (Except for jumps)");
}

/*
**	Usage
*/

static void	usage(char *cw)
{
	ft_printf("%{MAGENTA}s %{RED}s %{CYAN}s %{BLUE}s\n", "Usage:", cw,
		"[-dump N -s N -v N -ncurses] [-n N]", "<champion1.cor> <...>");
	ft_printf("%{GREEN}s\n",
		"###################### CHOOSE CHAMPION NUMBER ######################");
	ft_printf("    %{CYAN}s %{BLUE}s %{CYAN}s\n", "-n N", "<champion.cor>",
		":\t Set the champion as number N");
	ft_printf("%{GREEN}s\n",
		"######################### TEXT OUTPUT MODE #########################");
	ft_printf("    %{CYAN}s\n",
		"-d N\t: Dumps memory after N cycles then exits");
	ft_printf("    %{CYAN}s\n",
		"-s N\t: Runs N cycles, dumps memory, pauses, then repeats");
	ft_printf("    %{CYAN}s\n",
		"-v N\t: Verbosity levels, can be added together to enable several");
	usage_verbosity();
	ft_printf("%{GREEN}s\n",
		"####################### NCURSES OUTPUT MODE ########################");
	ft_printf("    %{CYAN}s\n", "-ncurses\t: Ncurses output mode");
	ft_printf("%{GREEN}s\n",
		"####################################################################");
	exit(EXIT_SUCCESS);
}

/*
**	Bienvenue sur Corewar - VM
*/

int			main(int ac, char **av)
{
	int			win;
	t_vm		vm;

	if (ac < 2)
		usage(*av);
	init_vm(&vm);
	if (!check_arg(&vm, ac, av))
		error(&vm, "no player");
	if (vm.ncurses)
		init_ncurses();
	initialisation(&vm);
	exe(&vm);
	if (vm.ncurses)
	{
		while (getch() == -1)
			;
		endwin();
	}
	win = get_winner(&vm);
	ft_printf("Contestant %d, \"%s\", has won !\n",
			win + 1, vm.player[win].name);
	return (0);
}
