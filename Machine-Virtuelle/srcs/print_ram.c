/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ram.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 10:42:45 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/24 11:34:10 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_ram(t_vm *vm)
{
	int	i;
	int	line;

	i = -1;
	line = ft_sqrt(MEM_SIZE);
	if (!line)
		return ;
	while (++i < MEM_SIZE)
	{
		if (!(i % line))
			ft_printf("%#.4x : ", i);
		ft_printf("%02x ", vm->ram[i].mem);
		if (i / line != (i + 1) / line)
			ft_putchar('\n');
	}
}
