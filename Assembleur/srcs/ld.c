/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:17:11 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/24 18:36:08 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	get_first_param(char *s, t_inst *new, t_champ *pl)
{
	int	tmp;

	if ((tmp = is_direct(s, pl, 1, new)))
	{
		new->size_one[0] = 4;
		new->size_two[1] = DIR_CODE;
		if (tmp == 1)
			new->param_one = itohex(ft_atoi(&(s[1])), 4);
	}
	else if (ft_atoi(s))
	{
		new->param_one = itohex(ft_atoi(s), 2);
		new->size_one[0] = 2;
		new->size_one[1] = IND_CODE;
	}
	return (new->size_one[0]);
}

static int	get_second_param(char *s, t_inst *new)
{
	int	i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i++] != 'r' || !(ft_isdigit(s[i])))
		return (0);
	new->param_two = itohex(ft_atoi(&(s[i])), 1);
	new->size_two[0] = 1;
	new->size_two[1] = REG_CODE;
	return (1);
}

t_champ		*make_ld(t_champ *pl, char *s)
{
	char	**tab;
	t_inst	*new;

	tab = ft_strsplit((char const*)(&(s[2])), SEPARATOR_CHAR);
	if (ft_tablen(tab) != 2)
		return (NULL); //a revoir
	new = (new_instruction("ld\0", &pl));
	new->opcode = 2;
	if (!(new->size_one[0] = get_first_param(tab[0], new, pl)))
		return (NULL); //a revoir
	if (!(new->size_two[0] = get_second_param(tab[0], new)))
		return (NULL);
	new->ocp = get_ocp(new);
	new->size = new->size_one[0] + new->size_two[0] + 2;
	new->pc = pl->current_pc;
	pl->current_pc += new->size;
	return (pl);
}
