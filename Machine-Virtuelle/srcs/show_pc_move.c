/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_pc_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:04:51 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/03 17:07:07 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Montre les mouvements de pc avec -v 16
*/

void	show_pc_move(t_vm *vm, int last_pc, int pc)
{
	while (last_pc < 0)
		last_pc += MEM_SIZE;
	ft_printf("ADV %d (0x%04x -> 0x%04x)", pc - last_pc, last_pc, pc);
	while (last_pc < pc)
	{
		ft_printf(" %02x", vm->ram[last_pc % MEM_SIZE].mem);
		++last_pc;
	}
	ft_printf("\n");
}
