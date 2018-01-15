/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbradel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:07:58 by gbradel           #+#    #+#             */
/*   Updated: 2018/01/12 17:08:05 by gbradel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_ncurses(WINDOW **w)
{
	*w = initscr();
	if (has_colors() == FALSE)
	{
		ft_printf("Your terminal does not support colors.\n");
		endwin();
		exit(1);
	}
	start_color(); // start color
	cbreak(); //getch() no block
	curs_set(0);
	nodelay(*w, TRUE);
}
