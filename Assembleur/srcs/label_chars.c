/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 17:00:24 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/18 19:38:00 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		how_many_label_char(char *s)
{
	int		count;
	int		i;
	int		j;
	char	*to_compare;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	to_compare = LABEL_CHARS;
	while (s[i] && i == count)
	{
		j = -1;
		while (to_compare[++j])
			if (to_compare[j] == s[i])
				count++;
		i++;
	}
	if (s[i - 1] == LABEL_CHAR)
		return (count);
	else
		return (0);
}
