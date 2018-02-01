/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:14 by ahouel            #+#    #+#             */
/*   Updated: 2018/02/01 14:36:49 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	keys_press(t_vm *vm, char key)
{
	if (key == ' ' && vm->pause)
	{
		vm->pause = 0;
		attron(COLOR_PAIR(30));
		mvprintw(1, 216, "~ ~ PAUSED ~ ~");
		attroff(COLOR_PAIR(30));
	}
	if (key == 'w')
	{
		if (vm->delay + 10000 < 410000)
			vm->delay += 10000;
	}
	else if (key == 'e')
	{
		if (vm->delay - 10000 > 0)
			vm->delay -= 10000;
	}
	ncurses_colors_init(key);
}

void		ncurses_controller(t_vm *vm)
{
	char	key;

	key = -1;
	call_ncurses(vm);
	while ((key = getch()) != -1)
		keys_press(vm, key);
	while (!vm->pause)
	{
		key = getch();
		if (key != -1)
		{
			keys_press(vm, key);
			refresh_all(vm);
			if (key == ' ')
			{
				vm->pause = 1;
				attron(COLOR_PAIR(31));
				mvprintw(1, 216, "~ ~  PLAY  ~ ~");
				break ;
			}
		}
	}
}
