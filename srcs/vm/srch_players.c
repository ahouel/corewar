/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srch_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:45:34 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/10 10:13:37 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Fix 2 joueur avec un slot libre entre
*/

static int	srch_nb_player(int argc, char **argv, int arg_num)
{
	if (arg_num - 2 > 0)
		if (ft_strstr(argv[arg_num - 2], "-n"))
			return (1);
	return (0);
}

static int	get_nb_player(t_vm *vm, int argc, char **argv, int arg_num)
{
	int ret;

	ret = 0;
	if (srch_nb_player(argc, argv, arg_num))
	{
		ret = ft_atoi(argv[arg_num - 1]);
		if (ret > 0 && ret < MAX_PLAYERS + 1)
			return (ret);
	}
	return (0);
}

static void	new_player(t_vm *vm, int nb, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (nb != 0)
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

static void	init_players(t_vm *vm)
{
	int	i;

	i = 0;
	while (++i < MAX_PLAYERS + 1)
	{
		vm->player[i].active = 0;
		vm->player[i].life_signal = 0;
		vm->player[i].file_name = NULL;
		vm->player[i].name = NULL;
		vm->player[i].last_live = 0;
	}
}

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
