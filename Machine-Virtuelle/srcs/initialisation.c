/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:19:53 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/17 19:00:34 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Creation d'un processus par joueur
*/

static void	init_process(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].active)
			create_processus(vm, i);
		i++;
	}
}

/*
**	Ecriture des joueurs sur la ram et creation des processus.
**	Appel de write : i le num du joueur (joueur[i - 1]) et j : le combien
**	eme joueur on pose.
*/

void		initialisation(t_vm *vm)
{
	int i;
	int j;

	i = -1;
	j = 0;
	ft_printf("Introducing contestants...\n");
	if (!vm->nb_player)
		error(vm, "need at least 1 player to run corewar");
	while (++i < MAX_PLAYERS)
	{
		if (vm->player[i].active)
		{
			++j;
			write_players(vm, i, j);
		}
	}
	init_process(vm);
}
