/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:33:15 by lchety            #+#    #+#             */
/*   Updated: 2017/11/08 17:27:55 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	keys_press(t_vm *vm, char key)
{
	if (key == ' ' && vm->pause != 1)
	{
		vm->pause = 1;
		mvprintw(2, 3 * (MEM_SIZE / 64) + 6, "** PAUSED **");
	}
	if (key == 'w')
	{
		if (vm->delay + 24000 < 1000000)
			vm->delay += 24000;
	}
	else if (key == 'e')
	{
		if (vm->delay - 12000 > 0)
			vm->delay -= 12000;
		else
			vm->delay = 0;
	}
}

void		controller(t_vm *vm)
{
	char	key;

	key = -1;
	key = getch();
	if (key != -1)
	{
		keys_press(vm, key);
	}
	while (vm->pause)
	{
		key = getch();
		if (key != -1)
		{
			keys_press(vm, key);
			call_ncurses(vm);
			if (key == ' ')
			{
				vm->pause = 0;
				break ;
			}
		}
		sleep(1);
	}
}
