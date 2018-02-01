/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_labels_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 17:03:22 by lgaveria          #+#    #+#             */
/*   Updated: 2018/02/01 14:57:21 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	Fait la difference entre le PC actuel et selui qu'on cherche a atteindre via
**	un addressage de type %:xxx. Le calcul se fait differement selon le sens de
**	la soustraction.
*/

static char		*get_val(t_inst *cur, t_champ *pl, char *s, int param)
{
	t_lab	*lab;
	int		size;

	lab = pl->lab;
	while (lab && ft_strcmp(lab->name, s) != 0)
		lab = lab->next;
	if (!lab)
		exit_free("wrong parametre at the line ", pl, NULL, cur->line);
	size = 0;
	if (cur->op->p_type[param] == T_LAB)
		size = cur->op->dir_size;
	else if (cur->op->p_type[param] == T_ILAB)
		size = 2;
	if (lab->pc < cur->pc)
		return (itohex(65536 - ((cur->pc - lab->pc) % 65536), size));
	return (itohex((lab->pc - cur->pc) % 65536, size));
}

/*
** Parcourt nos listes chainees a la recherche des addressage par label.
*/

t_champ			*fill_label_params(t_champ *pl)
{
	t_lab	*lab;
	t_inst	*ins;
	int		i;

	lab = pl->lab;
	while (lab)
	{
		ins = lab->lst;
		while (ins)
		{
			i = 0;
			while (i < ins->op->nb_param)
			{
				if (ins->lab_name[i])
					ins->op->params[i] = get_val(ins, pl, ins->lab_name[i], i);
				i++;
			}
			ins = ins->next;
		}
		lab = lab->next;
	}
	return (pl);
}
