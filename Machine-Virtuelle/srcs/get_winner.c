/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_winner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:01:14 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/10 17:55:10 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Regarde les joueurs, le dernier a avoir fait un live win
*/

int	get_winner(t_vm *vm)
{
	int i;
	int best;

	i = -1;
	best = 0;
	while (++i < vm->nb_player)
		if (vm->player[i].last_live > vm->player[best].last_live)
			best = i;
	return (best);
}
