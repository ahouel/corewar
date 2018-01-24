/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:12:32 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/24 18:15:30 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_champ		*make_xor(t_champ *pl, char *s)
{
	t_lab		*lab;
	t_inst		*inst;

	pl = make_and(pl, s);
	lab = pl->lab;
	while (lab->next)
		lab = lab->next;
	inst = lab->lst;
	while (inst->next)
		inst = inst->next;
	free(inst->name);
	inst->name = ft_strdup("xor");
	inst->opcode = 8;
	return (pl);
}
