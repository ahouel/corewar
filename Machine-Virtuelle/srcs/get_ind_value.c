/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ind_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 17:47:09 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/03 14:32:04 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Prend la valeur (int 4 octets) a l'adresse addr
*/

int	get_ind_value(t_vm *vm, int addr)
{
	int	value;

	while (addr < 0)
		addr += MEM_SIZE;
	value = 0;
	value = vm->ram[addr % MEM_SIZE].mem;
	value <<= 8;
	value |= vm->ram[(addr + 1) % MEM_SIZE].mem;
	value <<= 8;
	value |= vm->ram[(addr + 2) % MEM_SIZE].mem;
	value <<= 8;
	value |= vm->ram[(addr + 3) % MEM_SIZE].mem;
	return (value);
}
