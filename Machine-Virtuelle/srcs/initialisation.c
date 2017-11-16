/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:19:53 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 17:13:12 by ahouel           ###   ########.fr       */
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
			add_process(vm, create_processus(vm, i));
		i++;
	}
}

/*
**	Ecriture des joueurs sur la ram et creation des processus.
*/

void		initialisation(t_vm *vm)
{
	int i;
	int j;

	i = 1;
	j = 0;
	ft_printf("Introducing contestants...\n");
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].active)
		{
			write_players(vm, i, j);
			j++;
		}
		i++;
	}
	init_process(vm);
}
