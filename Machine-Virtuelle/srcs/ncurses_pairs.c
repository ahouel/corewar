/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_pairs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:58:27 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/24 16:59:32 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ncurses_pairs(void)
{
	init_pair(0, 0, 0);
	init_pair(5, 50, 0);
	init_pair(6, 60, 0);
	init_pair(7, 70, 0);
	init_pair(8, 80, 0);
	init_pair(10, 50, 55);
	init_pair(11, 60, 65);
	init_pair(12, 70, 75);
	init_pair(13, 80, 85);
	init_pair(15, 55, 0);
	init_pair(16, 65, 0);
	init_pair(17, 75, 0);
	init_pair(18, 85, 0);
	init_pair(25, 40, 50);
	init_pair(26, 40, 60);
	init_pair(27, 40, 70);
	init_pair(28, 40, 80);
	init_pair(42, 35, 35);
	init_pair(20, 35, 0);
	init_pair(30, 1, 0);
	init_pair(31, 2, 0);
	init_pair(40, 40, 0);
}
