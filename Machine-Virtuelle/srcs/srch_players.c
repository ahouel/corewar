/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srch_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:23:22 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/17 15:07:10 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Fix 2 joueur avec un slot libre entre
*/

/*
**	On cherche s'il y a un -n
*/

static int	srch_nb_player(int argc, char **argv, int arg_num)
{
	if (arg_num - 2 > 0)
		if (ft_strstr(argv[arg_num - 2], "-n"))
			return (1);
	return (0);
}

/*
**	On prend le nombre apres un -n
*/

static int	get_nb_player(t_vm *vm, int argc, char **argv, int arg_num)
{
	int ret;

	ret = 0;
	if (srch_nb_player(argc, argv, arg_num))
	{
		ret = ft_atoi(argv[arg_num - 1]);
		if (ret < 1 || ret > MAX_PLAYERS)
			error("-n wrong number\n");
		return (ret - 1);
	}
	return (-1);
}

/*
**	Creation d'un nouveau joueur, set ses variables
*/

static void	new_player(t_vm *vm, int nb, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (nb > -1)
	{
		if (!vm->player[nb].life_signal && !vm->player[nb].file_name)
		{
			vm->player[nb].life_signal = 1;
			vm->player[nb].file_name = str;
		}
		else if (vm->player[nb].life_signal && vm->player[nb].file_name)
		{
			error("Too much players on the same slot with \"-n\"\n");
		}
		else
		{
			vm->player[nb].life_signal = 1;
			tmp = vm->player[nb].file_name;
			vm->player[nb].file_name = str;
			new_player(vm, 0, tmp);
		}
	}
	else
	{
		while (vm->player[++nb].file_name)
			;
		vm->player[nb].file_name = str;
	}
	vm->player[nb].active = 1;
}

/*
**	Init du tableau de joueurs
*/

static void	init_players(t_vm *vm)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
		ft_bzero(&vm->player[i], sizeof(t_player));
}

/*
**	Recherche des .cor dans les arguments
*/

int			srch_players(t_vm *vm, int argc, char **argv)
{
	int		i;
	char	*tmp;

	i = 1;
	init_players(vm);
	vm->nb_player = 0;
	while (i < argc)
	{
		if ((tmp = ft_strstr(argv[i], ".cor")) && !tmp[4])
		{
			vm->nb_player++;
			if (vm->nb_player > MAX_PLAYERS)
				error("Too many champs\n");
			new_player(vm, get_nb_player(vm, argc, argv, i), argv[i]);
		}
		i++;
	}
	if (!vm->nb_player)
		return (0);
	return (1);
}
