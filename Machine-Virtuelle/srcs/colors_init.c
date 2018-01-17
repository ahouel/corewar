/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbradel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:14:53 by gbradel           #+#    #+#             */
/*   Updated: 2018/01/17 19:07:40 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	color_one(void)
{
	init_color(35, 350, 350, 350);// basic grey -> ecriture des bordures et de la ram
	init_color(40, 1000, 1000, 1000);// basic white -> all stats sur le cote
	init_color(50, 102, 1000, 1000); // fluo blue -> p1
	init_color(60, 1000, 302, 824); // fluo pink -> p2
	init_color(70, 102, 1000, 102); // fluo green -> p3
	init_color(80, 1000, 1000, 102); // fluo yellow -> p4
	init_color(55, 51, 500, 500); // processus p1
	init_color(65, 500, 151, 412); // processus p2
	init_color(75, 51, 500, 51); // processus p3
	init_color(85, 500, 500, 51); // processus p4
	init_color(0, 0, 0, 0); // fond
	init_color(1, 921, 0, 0); // pause
	init_color(2, 0, 600, 0); // play
}

static void	color_two(void)
{
	init_color(35, 400, 647, 678);//  -> ecriture des bordures et de la ram
	init_color(40, 769, 875, 902);//  -> all stats sur le cote
	init_color(50, 275, 129, 102); //  -> p1
	init_color(60, 412, 239, 239); //  -> p2
	init_color(70, 729, 333, 212); //  -> p3
	init_color(80, 643, 220, 125); //  -> p4
	init_color(55, 137, 65, 51); // processus p1
	init_color(65, 206, 119, 119); // processus p2
	init_color(75, 364, 166, 106); // processus p3
	init_color(85, 321, 110, 62); // processus p4
	init_color(0, 0, 231, 275); // fond
	init_color(1, 921, 0, 0); //  pause
	init_color(2, 0, 600, 0); // play
}

static void	do_pair(t_vm *vm)
{
	init_pair(5, 50, 0); // fluo blue on black -> paire p1
	init_pair(6, 60, 0); // fluo pink on black -> paire p2
	init_pair(7, 70, 0); // fluo green on black -> paire p3
	init_pair(8, 80, 0); // fluo yellow on black -> paire p4
	init_pair(10, 50, 55); // fluo blue on black for ps -> paire ps p1
	init_pair(11, 60, 65); // fluo pink on black for ps -> paire ps p2
	init_pair(12, 70, 75); // fluo green on black for ps -> paire ps p3
	init_pair(13, 80, 85); // fluo yellow on black for ps -> paire ps p4
	init_pair(42, 35, 35); // paire bordure
	init_pair(20, 35, 0); // ram de base
	init_pair(30, 1, 0); // ecriture de paused
	init_pair(31, 2, 0); // ecriture de play
	init_pair(40, 40, 0); // stats sur la droite
	vm->player[0].id_color = 5;
	vm->player[1].id_color = 6;
	vm->player[2].id_color = 7;
	vm->player[3].id_color = 8;
}

void		colors_init(t_vm *vm)
{
	color_one();
	color_two();
	do_pair(vm);
}
