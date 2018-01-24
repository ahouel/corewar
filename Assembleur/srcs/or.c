/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:05:42 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/24 18:11:19 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
** Voir le commentaire de make_sub
*/

t_champ		*make_or(t_champ *pl, char *s)
{
	t_lab	*lab;
	t_inst	*inst;

	pl = make_and(pl, s);
	lab = pl->lab;
	while (lab->next)
		lab = lab->next;
	inst = lab->lst;
	while (inst->next)
		inst = inst->next;
	free(inst->name);
	inst->name = ft_strdup("or");
	inst->opcode = 7;
	return (pl);
}
