/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 14:42:39 by lchety            #+#    #+#             */
/*   Updated: 2017/11/10 15:43:08 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_process(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].active)
			add_process(vm, create_process(vm, i * (-1)));
		i++;
	}
}

void		initialisation(t_vm *vm)
{
	int i;
	int j;

	i = 1;
	j = 0;
	ft_bzero(&vm->ram, sizeof(t_mem) * MEM_SIZE);
	while (i < MAX_PLAYERS + 1)
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
