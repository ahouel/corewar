/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 18:39:30 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/06 19:14:31 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	get_first_param(char *s, t_inst *new, t_champ *pl)
{
	int	i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i] == 'r' && ft_isdigit(s[i + 1]))
	{
		new->param_one = itohex(ft_atoi(&(s[i + 1])), 1);
		new->size_one[0] = 1;
		new->size_one[1] = 1;
	}
	else if (is_direct(&(s[i]), pl, 1, new) && !(new->one_label_name))
	{
		new->param_one = itohex(ft_atoi(&(s[i + 1])), 4);
		new->size_one[0] = 4;
		new->size_one[1] = 2;
	}
	else if (ft_atoi(&(s[i])))
	{
		new->param_one = itohex(ft_atoi(&(s[i])), 2);
		new->size_one[0] = 2;
		new->size_one[1] = 3;
	}
	return (new->size_one[0]);
}

static int	get_second_param(char *s, t_inst *new, t_champ *pl)
{
	int	i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i] == 'r' && ft_isdigit(s[i + 1]))
	{
		new->param_two = itohex(ft_atoi(&(s[i + 1])), 1);
		new->size_two[0] = 1;
		new->size_two[1] = 1;
	}
	else if (is_direct(&(s[i]), pl, 1, new) && !(new->two_label_name))
	{
		new->param_two = itohex(ft_atoi(&(s[i + 1])), 4);
		new->size_two[0] = 4;
		new->size_two[1] = 2;
	}
	else if (ft_atoi(&(s[i])))
	{
		new->param_two = itohex(ft_atoi(&(s[i])), 2);
		new->size_two[0] = 2;
		new->size_two[1] = 3;
	}
	return (new->size_two[0]);
}

static int	get_third_param(char *s, t_inst *new)
{
	int	i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i++] != 'r' || !(ft_isdigit(s[i])))
		return (0);
	new->param_three = itohex(ft_atoi(&(s[i])), 1);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] && !(ft_iswhitespace(s[i])))
		return (0);
	new->size_three[1] = 1;
	return (1);
}

t_champ		*make_and(t_champ *pl, char *s)
{
	char	**tab;
	t_inst	*new;
	int		i;

	tab = ft_strsplit((char const*)(&(s[3])), SEPARATOR_CHAR);
	if (ft_tablen(tab) != 3)
		return (NULL); //a revoir
	new = new_instruction("and\0", &pl);
	new->opcode = 6;
	if (!(new->size_one[0] = get_first_param(tab[0], new, pl)))
		return (NULL); //a revoir
	if (!(new->size_two[0] = get_second_param(tab[1], new, pl)))
		return (NULL);
	if (!(new->size_three[0] = get_third_param(tab[2], new)))
		return (NULL);
	new->ocp = get_ocp(new);
	new->size = new->size_one[0] + new->size_two[0] + new->size_three[0];
	new->pc = pl->current_pc;
	pl->current_pc += new->size;
	return (pl);
}
