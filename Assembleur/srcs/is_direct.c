/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_direct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:11:43 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/06 18:26:19 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	is_label_chars(char c)
{
	char	*chars;
	int		i;

	chars = LABEL_CHARS;
	i = 0;
	while (chars[i])
	{
		if (chars[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int			is_direct(char *s, t_champ *pl, int param, t_inst *new)
{
	int		i;
	int		count;
	int		ret;

	i = 0;
	ret = 0;
	if (!s || s[i++] != '%')
		return (0);
	if (s[i] && s[i] == LABEL_CHAR)
	{
		count = 0;
		while (s[++i] && is_label_chars(s[i]))
			count++;
		if (param == 1)
			new->one_label_name = ft_strsub(s, 2, count);
		if (param == 2)
			new->two_label_name = ft_strsub(s, 2, count);
		if (param == 3)
			new->three_label_name = ft_strsub(s, 2, count);
		ret = 2;
	}
	else if (s[i] && ft_isdigit(s[i]))
		while (ft_isdigit(s[i++]))
			ret = 1;
	return (ret);
}
