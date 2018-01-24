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

static char		*get_value(t_inst *current, t_champ *pl, char *s)
{
	t_lab	*lab;

	lab = pl->lab;
	while (lab && ft_strcmp(lab->name, s) != 0)
		lab = lab->next;
	if (!lab)
		return (NULL); //a revoir
//	int ttmp = (current->pc - lab->pc) % 65536;
//	printf("|| %d ||\n", ttmp);
	if (lab->pc < current->pc)
		return (itohex(65531, 2));
//		return (itohex(65536 - ((current->pc - lab->pc) % 65536), 2));
	return (itohex((lab->pc - current->pc) % 65536, 2));
}

static t_champ	*fill_params(t_champ *pl)
{
	t_lab	*lab;
	t_inst	*inst;

	lab = pl->lab;
	while (lab)
	{
		inst = lab->lst;
		while (inst)
		{
			if (inst->one_label_name)
				inst->param_one = get_value(inst, pl, inst->one_label_name);
			if (inst->two_label_name)
				inst->param_two = get_value(inst, pl, inst->two_label_name);
			if (inst->three_label_name)
				inst->param_three = get_value(inst, pl, inst->three_label_name);
			inst = inst->next;
		}
		lab = lab->next;
	}
	return (pl);
}

t_champ			*get_labels_params(t_champ *pl)
{
	t_lab	*lab;

	lab = pl->lab;
	while (lab)
	{
		lab->pc = lab->lst->pc;
		lab = lab->next;
	}
	pl = fill_params(pl);
	return (pl);
}
