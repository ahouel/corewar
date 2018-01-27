/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_colors_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbradel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:14:53 by gbradel           #+#    #+#             */
/*   Updated: 2018/01/24 17:01:03 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	color_one(void)
{
	init_color(35, 350, 350, 350);
	init_color(40, 1000, 1000, 1000);
	init_color(50, 102, 1000, 1000);
	init_color(60, 1000, 302, 824);
	init_color(70, 102, 1000, 102);
	init_color(80, 1000, 1000, 102);
	init_color(55, 51, 500, 500);
	init_color(65, 500, 151, 412);
	init_color(75, 51, 500, 51);
	init_color(85, 500, 500, 51);
	init_color(0, 0, 0, 0);
	init_color(1, 921, 0, 0);
	init_color(2, 0, 600, 0);
}

static void	color_one_bis(void)
{
	init_color(35, 651, 651, 651);
	init_color(40, 0, 0, 0);
	init_color(50, 894, 12, 0);
	init_color(60, 0, 698, 176);
	init_color(70, 886, 24, 898);
	init_color(80, 4, 16, 898);
	init_color(55, 953, 502, 502);
	init_color(65, 502, 851, 588);
	init_color(75, 949, 502, 949);
	init_color(85, 502, 502, 949);
	init_color(0, 1000, 1000, 1000);
	init_color(1, 82, 871, 1000);
	init_color(2, 0, 600, 0);
}

static void	color_two(void)
{
	init_color(35, 400, 647, 678);
	init_color(40, 769, 875, 902);
	init_color(50, 275, 129, 102);
	init_color(60, 412, 239, 239);
	init_color(70, 729, 333, 212);
	init_color(80, 643, 220, 125);
	init_color(55, 137, 65, 51);
	init_color(65, 206, 119, 119);
	init_color(75, 364, 166, 106);
	init_color(85, 321, 110, 62);
	init_color(0, 0, 231, 275);
	init_color(1, 921, 0, 0);
	init_color(2, 0, 600, 0);
}

static void	color_two_bis(void)
{
	init_color(35, 600, 357, 325);
	init_color(40, 0, 0, 0);
	init_color(50, 725, 875, 898);
	init_color(60, 588, 765, 765);
	init_color(70, 275, 671, 788);
	init_color(80, 361, 780, 878);
	init_color(55, 867, 937, 953);
	init_color(65, 796, 882, 882);
	init_color(75, 639, 835, 894);
	init_color(85, 682, 890, 937);
	init_color(0, 1000, 773, 725);
	init_color(1, 82, 871, 1000);
	init_color(2, 0, 600, 0);
}

void		ncurses_colors_init(char color)
{
	if (color == '1')
		color_one();
	else if (color == '!')
		color_one_bis();
	else if (color == '2')
		color_two();
	else if (color == '@')
		color_two_bis();
	ncurses_pairs();
}
