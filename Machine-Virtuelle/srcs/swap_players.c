/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:24:44 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/15 16:26:06 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Echange de place je joueur souhaite avec -n
**	Et celui qui y etait sans -n
*/

void	swap_players(t_vm *vm, int nb, char *str)
{
	char	*tmp;

	tmp = NULL;
	vm->player[nb].lives_count = 1;
	tmp = vm->player[nb].file_name;
	vm->player[nb].file_name = str;
	new_player(vm, -1, tmp);
}
