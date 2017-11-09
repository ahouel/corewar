/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 11:49:01 by lchety            #+#    #+#             */
/*   Updated: 2017/11/09 16:02:13 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
			error("error : verbosity bad number\n");
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
			error("error : dump bad number\n");
	}
	return (0);
}

static int	srch_ncurses(int argc, char **argv)
{
	int ret;

	ret = 0;
	if ((ret = ft_strargv(argc, argv, "-ncurses")))
		return (1);
	return (0);
}

int			check_arg(t_vm *vm, int argc, char **argv)
{
	vm->dump = srch_nb_dump(argc, argv);
	vm->ncurses = srch_ncurses(argc, argv);
	vm->verbosity = srch_verbose(argc, argv);
	if (srch_players(vm, argc, argv))
		return (1);
	return (0);
}
