/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_label_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:36:48 by lgaveria          #+#    #+#             */
/*   Updated: 2018/02/01 12:44:50 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		is_label_char(char c, t_champ *pl)
{
	int		i;
	char	*to_compare;

	if (!c)
		return (0);
	if (!(to_compare = LABEL_CHARS))
		exit_free("undefined label_chars\n", pl, NULL, 0);
	i = 0;
	while (to_compare[i])
	{
		if (to_compare[i] == c)
			return (1);
		i++;
	}
	return (0);
}
