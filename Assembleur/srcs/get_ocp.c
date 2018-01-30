/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ocp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 19:07:57 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/29 18:32:47 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	get_ocp(t_op *current)
{
	char	ocp;
	int		i;

	i = 0;
	while (i < 3)
	{
		if (current->p_type[i] == T_IND || current->p_type[i] == T_ILAB)
			current->p_type[i] = IND_CODE;
		if (current->p_type[i] == T_LAB)
			current->p_type[i] = DIR_CODE;
		i++;
	}
	ocp = current->p_type[0] * 64;
	ocp += current->p_type[1] * 16;
	ocp += current->p_type[2] * 4;
	return (ocp);
}
