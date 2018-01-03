/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 16:13:22 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/03 17:44:40 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Verifie si l'ocp est valide par rapport aux directives donnees
**	par le g_op_tab[]
*/

int			ocp_is_valid(t_vm *vm, t_pcb *proc, unsigned char ocp)
{
	int				i;
	unsigned char	param;
	unsigned char	mask;

	i = -1;
	while (++i < proc->op->nb_arg)
	{
		mask = 0xC0;
		mask = mask >> (2 * i);
		param = ocp & mask;
		param = param >> (6 - (2 * i));
		if (!(param & proc->op->param_type[i]))
		{
			proc->op->func = NULL;
			proc->pc++;
			return (0);
		}
	}
	return (1);
}
