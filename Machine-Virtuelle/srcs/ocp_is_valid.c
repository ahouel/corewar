/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 16:13:22 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/17 19:02:26 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Regarde la correspondance entre le param trouve dans l'ocp
**	et le param_type de g_op_tab[]
*/

static int	check_type(unsigned char param, int param_type)
{
	if (param == REG_CODE)
		if (param_type & T_REG)
			return (1);
	if (param == DIR_CODE)
		if (param_type & T_DIR)
			return (1);
	if (param == IND_CODE)
		if (param_type & T_IND)
			return (1);
	return (0);
}

/*
**	Verifie si l'ocp est valide par rapport aux directives donnees
**	par le g_op_tab[]
**	En bref : si l'ocp annonce un type qui n'est de base pas supporte par
**	le label, revoit 0. Sinon 1
*/

int			ocp_is_valid(t_pcb *proc, unsigned char ocp)
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
		if (!check_type(param, proc->op->param_type[i]))
		{
			proc->op->func = NULL;
			return (0);
		}
	}
	return (1);
}
