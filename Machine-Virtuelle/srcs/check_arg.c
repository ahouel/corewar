/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:17:54 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/17 15:20:21 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	srch_nb_dump(int argc, char **argv)
{
	int ret;
	int nb;

	ret = 0;
	nb = 0;
	if ((ret = ft_strargv(argc, argv, "-dump")))
	{
		if ((ret + 1) < argc && ft_str_isdigit(argv[ret + 1]))
			return (ft_atoi(argv[ret + 1]));
		else
			error("error : dump wrong number\n");
	}
	return (-1);
}

static int	srch_verbose(int argc, char **argv)
{
	int ret;
	int nb;

	ret = 0;
	nb = 0;
	if ((ret = ft_strargv(argc, argv, "-v")))
	{
		if ((ret + 1) < argc && ft_str_isdigit(argv[ret + 1]))
			return (ft_atoi(argv[ret + 1]));
		else
			error("error : verbosity wrong number\n");
	}
	return (0);
}

static int	srch_ncurses(int argc, char **argv)
{
	if (ft_strargv(argc, argv, "-ncurses"))
		return (1);
	return (0);
}

static int	srch_debug(int argc, char **argv)
{
	int	ret;

	ret = 0;
	if ((ret = ft_strargv(argc, argv, "-debug")))
	{
		if ((ret + 1) < argc && ft_str_isdigit(argv[ret + 1]))
			return (ft_atoi(argv[ret + 1]));
		else
			error("error : debug wrong number\n");
	}
	return (-1);
}

/*
**	On cherche -v -dump et -ncurses pour les stocker, puis les joueurs (.cor)
*/

int			check_arg(t_vm *vm, int argc, char **argv)
{
	vm->dump = srch_nb_dump(argc, argv);
	vm->ncurses = srch_ncurses(argc, argv);
	vm->verbosity = srch_verbose(argc, argv);
	vm->debug = srch_debug(argc, argv);
	if (!srch_players(vm, argc, argv))
		return (0);
	return (1);
}
