/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:17:54 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/11 14:52:31 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Regarde si l'argument[*i] est un -dump
*/

static int	srch_dump(t_vm *vm, int ac, char **av, int *i)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(av[*i], "-dump"))
	{
		if (vm->dump != 1)
			error(vm, "can't use twice -dump");
		if (*i + 1 < ac && ft_str_isdigit(av[*i + 1]))
		{
			ret = ft_atoi(av[++(*i)]);
			if (ret > -1)
				return (ret);
		}
		error(vm, "dump wrong number");
	}
	return (-1);
}

/*
**	Regarde si l'argument[*i] est un -v
*/

static int	srch_verbosity(t_vm *vm, int ac, char **av, int *i)
{
	int	ret;

	if (!ft_strcmp(av[*i], "-v"))
	{
		if (vm->verbosity)
			error(vm, "can't use twice -v");
		if (*i + 1 < ac && ft_str_isdigit(av[*i + 1]))
		{
			ret = ft_atoi(av[++(*i)]);
			if (ret > 0 && ret < V_MAX + 1)
				return (ret);
		}
		error(vm, "verbosity wrong number");
	}
	return (0);
}

/*
**	Regarde si l'argument arg est un -ncurses
*/

static int	srch_ncurses(t_vm *vm, char *arg)
{
	if (!ft_strcmp(arg, "-ncurses"))
	{
		if (vm->ncurses)
			error(vm, "can't use twice -ncurses");
		return (1);
	}
	return (0);
}

/*
**	On cherche -v -dump et -ncurses pour les stocker, puis les joueurs (.cor)
**	-v : verbosity -> affichages de differentes donnees
**	-ncurses : utilisation de ncurses -> interface graphique
**	-dump : dump dans les cycle -> sauter directement au cycle x
**	et afficher la memoire
**	TO DO : -s, bonus, gestion d'erreur a verifier
**	Re-set les lives_count a 0 pour tous
*/

int			check_arg(t_vm *vm, int ac, char **av)
{
	int	i;
	int	ret;

	i = 0;
	while (++i < ac)
	{
		if ((ret = srch_dump(vm, ac, av, &i)) > -1)
			vm->dump = ret;
		else if ((ret = srch_ncurses(vm, av[i])))
			vm->ncurses = ret;
		else if ((ret = srch_verbosity(vm, ac, av, &i)))
			vm->verbosity = ret;
		else if (!(srch_player(vm, ac, av, &i)))
		{
			ft_printf("%{RED}s %{BLUE}s\n",
					"Error : can't read source file ", av[i]);
			error(vm, "");
		}
	}
	i = -1;
	while (++i < MAX_PLAYERS)
		vm->player[i].lives_count = 0;
	return (vm->nb_player);
}
