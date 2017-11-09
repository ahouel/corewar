/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srch_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:45:34 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/09 16:01:06 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		srch_nb_player(int argc, char **argv, int arg_num)
{
	if (arg_num - 2 > 0)
		if (ft_strstr(argv[arg_num - 2], "-n"))
			return (1);
	return (0);
}

/*
**	si <f1> -n 1 <f2> a corrige au dessus
*/

int		is_free_nb_player(t_vm *vm, int nb)
{
	if (!vm->nb_player)
		return (1);
	if (vm->player[nb].active)
		return (0);
	return (1);
}

int		first_free_nb_player(t_vm *vm)
{
	int i;

	i = 1;
	while (i <= MAX_PLAYERS)
	{
		if (!vm->player[i].active)
			return (i);
		i++;
	}
	return (0);
}

int		get_nb_player(t_vm *vm, int argc, char **argv, int arg_num)
{
	int ret;

	ret = 0;
	if (srch_nb_player(argc, argv, arg_num))
	{
		ret = ft_atoi(argv[arg_num - 1]);
		if (ret > 0 && ret < 5 && is_free_nb_player(vm, ret))
			return (ret);
		else
			return (first_free_nb_player(vm));
	}
	else
		return (first_free_nb_player(vm));
	return (0);
}

static void	new_player(t_vm *vm, int nb, char *str)
{
	vm->player[nb].active = 1;
	vm->player[nb].life_signal = 0;
	vm->player[nb].file_name = str;
	vm->player[nb].name = NULL;
	vm->player[nb].last_live = 0;
}

int	srch_players(t_vm *vm, int argc, char **argv)
{
	int		i;
	char	*tmp;

	i = 1;
	vm->nb_player = 0;
	while (i < argc)
	{
		if ((tmp = ft_strstr(argv[i], ".cor")) && !tmp[4])
		{
			vm->nb_player++;
			if (vm->nb_player > 4)
				error("Too many champs\n");
			new_player(vm, get_nb_player(vm, argc, argv, i), argv[i]);
		}
		i++;
	}
	if (vm->nb_player)
		return (0);
	else
		return (1);
}
