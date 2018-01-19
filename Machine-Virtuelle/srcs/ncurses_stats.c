/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_stats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbradel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:16:44 by gbradel           #+#    #+#             */
/*   Updated: 2018/01/12 17:16:46 by gbradel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_stats(int *tab, t_vm *vm, int x, int y)
{
	int		i;
	int		tmp[MAX_PLAYERS];

	i = -1;
	while (++i < MAX_PLAYERS)
		tmp[i] = tab[i];
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		while (tmp[i] > 0)
		{
			attron(COLOR_PAIR(vm->player[i].id_color));
			mvprintw(y, x, "|");
			attroff(COLOR_PAIR(vm->player[i].id_color));
			x++;
			tmp[i]--;
		}
	}
	attron(COLOR_PAIR(40));
}

void		live_stats(t_vm *vm)
{
	int		total;
	int		i;
	int		tmp;
	int		tab[MAX_PLAYERS];

	total = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
		total += vm->player[i].lives_count;
	if (total == 0)
		return ;
	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->player[i].name)
		{
			tmp = (vm->player[i].lives_count * 100 * 48) / total;
			if (tmp % 100 > 50)
				tmp += 50;
			tab[i] = tmp / 100;
		}
	print_stats(tab, vm, 198, 54);
}
