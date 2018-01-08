/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:17:40 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/05 16:11:31 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_champ		*make_live(t_champ *pl, char *s)
{
	int		i;
	int		direct;
	t_inst	*new;

	i = 4;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i] != '%')
		return (pl); // a gerer
	i++;
	direct = ft_atoi(&(s[i]));
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] && !(ft_iswhitespace(s[i])))
		return (pl); // a gerer
	new = (new_instruction("live\0", &pl));
	new->size = 5;
	new->opcode = 1;
	new->param_one = itohex(direct, 4);
	new->size_one[0] = 4;
	new->pc = pl->current_pc;
	pl->current_pc += new->size;
	return (pl);
}
