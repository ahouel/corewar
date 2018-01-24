/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:54:42 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/24 18:05:04 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
** Je pense qu'il faudrait supprimer la variable name dans la structure t_inst.
** Comme ca on enverrai juste l'opcode en parametre supplementaire aux fonctions
** make_*, et ca permettrai de reutiliser les memes pour les instructions qui
** suivent le meme schema. L'opcode devrait alors correspondre a l'index du
** tableau de fonctions.
*/

t_champ		*make_sub(t_champ *pl, char *s)
{
	t_lab	*lab;
	t_inst	*inst;

	pl = make_add(pl, s);
	lab = pl->lab;
	while (lab->next)
		lab = lab->next;
	inst = lab->lst;
	while (inst->next)
		inst = inst->next;
	free(inst->name);
	inst->name = ft_strdup("sub");
	inst->opcode = 5;
	return (pl);
}
