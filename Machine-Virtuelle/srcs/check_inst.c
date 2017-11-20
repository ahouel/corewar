/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:04 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/20 10:49:00 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_reg(int nb)
{
	if (nb < 1 || nb > 16)
		return (0);
	return (1);
}

int		check_params(t_op *op)
{
	int i;

	i = 0;
	while (i < op_tab[op->code].nb_arg)
	{
		if (op->ocp[i] == REG_CODE)
			if (!check_reg(op->ocp[i]))
				return (0);
		i++;
	}
	return (1);
}
