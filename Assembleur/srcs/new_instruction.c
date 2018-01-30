/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:43:58 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/30 16:26:54 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	Initialise une nouvelle structure instruction puis la place correctement par
**	rapport aux labels. Initialise egalement le t_op qui y est lie.
*/

t_inst		*new_instruction(t_champ *pl, int i, int line)
{
	t_inst	*new;
	t_inst	*tmp;
	t_lab	*current_lab;

	if (!(new = ft_memalloc(sizeof(t_inst))))
		exit_free("unsuccesfull malloc\n", pl, NULL, 0);
	new->pc = pl->current_pc;
	if (!(new->op = ft_memalloc(sizeof(t_op))))
		exit_free("unsuccesfull malloc\n", pl, NULL, 0);
	new->op = ft_memcpy(new->op, &(g_op_tab[i]), sizeof(t_op));
	new->line = line;
	current_lab = pl->lab;
	if (!current_lab)
		current_lab = (new_label("origin_label", pl))->lab;
	while (current_lab->next)
		current_lab = current_lab->next;
	tmp = current_lab->lst;
	if (!tmp)
		current_lab->lst = new;
	else
		while (tmp->next)
			tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	return (new);
}
