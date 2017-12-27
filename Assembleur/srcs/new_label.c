/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:53:42 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/18 19:38:11 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_champ		*new_label(char *name, t_champ *champ)
{
	t_lab	*new;
	t_lab	*tmp;
	int		i;

	i = 0;
	while (ft_iswhitespace(name[i]))
		i++;
	name = &(name[i]);
	if (!(new = malloc(sizeof(t_lab))))
		return (NULL); // a gerer
	new->pc = 0;
	new->name = ft_strsub(name, 0, how_many_label_char(name));
	new->lst = NULL;
	new->next = NULL;
	tmp = (*champ).lab;
	if (!tmp)
		(*champ).lab = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (champ);
}
