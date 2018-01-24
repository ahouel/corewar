/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:26:37 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/24 15:52:35 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/asm.h"

static int	get_first_param(char *s, t_inst *new, t_champ *pl)
{
	int	tmp;

	if ((tmp = is_direct(s, pl, 1, new)))
	{
		new->size_one[0] = 2;
		if (tmp == 1)
			new->param_one = itohex(ft_atoi(&(s[1])), 2);
	}
	return (new->size_one[0]);
}

t_champ		*make_zjmp(t_champ *pl, char *s)
{
	char	**tab;
	t_inst	*new;
	int		i;

	tab = ft_strsplit((char const *)(&(s[4])), SEPARATOR_CHAR);
	if (ft_tablen(tab) != 1)
		return (NULL); //a revoir
	new = (new_instruction("zjmp\0", &pl));
	new->opcode = 9;
	i = 0;
	while (ft_iswhitespace(tab[0][i]))
		i++;
	if (!(new->size_one[0] = get_first_param(&(tab[0][i]), new, pl)))
		return (NULL);
	new->size = 3;
	new->pc = pl->current_pc;
	pl->current_pc += new->size;
	return (pl);
}
