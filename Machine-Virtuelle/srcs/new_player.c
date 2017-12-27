/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:27:21 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/15 16:28:26 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Creation d'un nouveau joueur, set ses variables
**	On utilise lives_count ici seulement pour mettre une prio
**	au -n nombre pour les joueurs
*/

void	new_player(t_vm *vm, int nb, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (nb > -1)
	{
		if (!vm->player[nb].lives_count && !vm->player[nb].file_name)
		{
			vm->player[nb].lives_count = 1;
			vm->player[nb].file_name = str;
		}
		else if (vm->player[nb].lives_count && vm->player[nb].file_name)
			error(vm, "too much players on the same slot with \"-n\"");
		else
			swap_players(vm, nb, str);
	}
	else
	{
		while (vm->player[++nb].file_name)
			;
		vm->player[nb].file_name = str;
	}
	vm->player[nb].active = 1;
}
