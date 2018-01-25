/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_labels_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 17:03:22 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/24 15:40:17 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	Fait la difference entre le PC actuel et selui qu'on cherche a atteindre via
**	un addressage de type %:xxx. Le calcul se fait differement selon le sens de
**	la soustraction.
*/

static char		*get_val(t_inst *current, t_champ *pl, char *s)
{
	t_lab	*lab;

	lab = pl->lab;
	while (lab && ft_strcmp(lab->name, s) != 0)
		lab = lab->next;
	if (!lab)
		return (NULL); //a revoir
	if (lab->pc < current->pc)
		return (itohex(65536 - ((current->pc - lab->pc) % 65536), 2));
	return (itohex((lab->pc - current->pc) % 65536, 2));
}

/*
**	Cette fonction finira surement très vite par s'integrer à la detection des
**	direct, pour ne pas avoir a tout reparcourir ainsi.
*/

t_champ			*fill_label_params(t_champ *pl)
{
	t_lab	*lab;
	t_inst	*inst;
	int		i;

	lab = pl->lab;
	while (lab)
	{
		inst = lab->lst;
		while (inst)
		{
			i = 0;
			while (i > 3)
			{
				if (inst->lab_name[i])
					inst->op->params[i] = get_val(inst, pl, inst->lab_name[i]);
			}
			inst = inst->next;
		}
		lab = lab->next;
	}
	return (pl);
}
