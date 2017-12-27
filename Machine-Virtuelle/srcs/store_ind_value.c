/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ind_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:00:32 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/19 18:25:12 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Ecrit sur la ram les 4 octet de l'int value
**	a l'addresse addr pour le joueur p
*/

void	store_ind_value(t_vm *vm, int addr, int value, int p)
{
	while (addr < 0)
		addr += MEM_SIZE;
	vm->ram[addr % MEM_SIZE].mem = value >> 24;
	vm->ram[addr % MEM_SIZE].num = p;
	vm->ram[(addr + 1) % MEM_SIZE].mem = (value >> 16) & 0xff;
	vm->ram[(addr + 1) % MEM_SIZE].num = p;
	vm->ram[(addr + 2) % MEM_SIZE].mem = (value >> 8) & 0xff;
	vm->ram[(addr + 2) % MEM_SIZE].num = p;
	vm->ram[(addr + 3) % MEM_SIZE].mem = value & 0xff;
	vm->ram[(addr + 3) % MEM_SIZE].num = p;
}
