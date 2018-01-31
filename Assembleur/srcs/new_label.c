/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:53:42 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/30 16:27:08 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	Creer est positionne un nouveau maillon dans la liste de labels. Les mallocs
**	sont verifiés.
*/

t_champ		*new_label(char *name, t_champ *pl)
{
	t_lab	*new;
	t_lab	*tmp;
	int		i;

	i = 0;
	if (!(new = ft_memalloc(sizeof(t_lab))))
		exit_free("unsuccesfull malloc", pl, NULL, 0);
	if (!(new->name = ft_strsub(name, 0, how_many_label_char(name))))
		exit_free("unsuccesfull malloc", pl, NULL, 0);
	new->pc = pl->current_pc;
	tmp = (*pl).lab;
	if (!tmp)
		(*pl).lab = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (pl);
}
