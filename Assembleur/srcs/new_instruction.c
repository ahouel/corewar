/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:43:58 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/18 19:38:08 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	Initialise une nouvelle structure instruction puis la place correctement par
**	rapport aux labels.
*/

t_inst		*new_instruction(char *name, t_champ **champ)
{
	t_inst	*new;
	t_inst	*tmp;
	t_lab	*current_lab;

	if (!(new = ft_memalloc(sizeof(t_inst))))
		return (NULL); //a gerer
	new->name = ft_strdup(name);
	current_lab = (*champ)->lab;
	if (!current_lab)
		current_lab = (new_label("origin_label", *champ))->lab;
	while (current_lab->next != NULL)
		current_lab = current_lab->next;
	tmp = current_lab->lst;
	if (!tmp)
		current_lab->lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}
