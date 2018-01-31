/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_label_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:36:48 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/30 16:25:57 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		is_label_char(char c)
{
	int		i;
	char	*to_compare;

	if (!c)
		return (0);
	to_compare = LABEL_CHARS;
	i = 0;
	while (to_compare[i])
	{
		if (to_compare[i] == c)
			return (1);
		i++;
	}
	return (0);
}
