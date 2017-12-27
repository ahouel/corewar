/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:14 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/30 17:02:42 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Control pour le ncurses
**	TO DO : le refaire proprement, changer le delay par un autre nom, idem
**	pour le nom du fichier .c (voir aue c'est dans la partie ncurses)
**	utiliser plutot usleep() que sleep()
*/


static void	keys_press(t_vm *vm, char key)
{
	if (key == ' ' && vm->pause)
	{
		vm->pause = 0;
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
	while (!vm->pause)
	{
		key = getch();
		if (key != -1)
		{
			keys_press(vm, key);
			call_ncurses(vm);
			if (key == ' ')
			{
				vm->pause = 1;
				break ;
			}
		}
		sleep(1);
	}
}
