/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:47:48 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/24 17:01:35 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	get_first_param(char *s, t_inst *new)
{
	int i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i++] != 'r' || !(ft_isdigit(s[i])))
		return (0);
	new->param_one = itohex(ft_atoi(&(s[i])), 1);
	new->size_one[1] = 1;
	return (1);
}


static int	get_second_param(char *s, t_inst *new)
{
	int i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i++] != 'r' || !(ft_isdigit(s[i])))
		return (0);
	new->param_two = itohex(ft_atoi(&(s[i])), 1);
	new->size_two[1] = 1;
	return (1);
}


static int	get_third_param(char *s, t_inst *new)
{
	int i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i++] != 'r' || !(ft_isdigit(s[i])))
		return (0);
	new->param_three = itohex(ft_atoi(&(s[i])), 1);
	new->size_three[1] = 1;
	return (1);
}

t_champ		*make_add(t_champ *pl, char *s)
{
	char	**tab;
	t_inst	*new;
	int		tmp;
	int		i;

	tab = ft_strsplit((char const *)(&(s[3])), SEPARATOR_CHAR);
	if (ft_tablen(tab) != 3)
		return (NULL); //a revoir
	new = (new_instruction("add\0", &pl));
	new->opcode = 4;
	if (!(new->size_one[0] = get_first_param(tab[0], new)))
		return (NULL); //a revoir
	if (!(new->size_two[0] = get_second_param(tab[0], new)))
		return (NULL); //a revoir
	if (!(new->size_three[0] = get_third_param(tab[0], new)))
		return (NULL); //a revoir
	new->ocp = get_ocp(new);
	new->size = 5;
	new->pc = pl->current_pc;
	pl->current_pc += new->size;
	return (pl);
}
