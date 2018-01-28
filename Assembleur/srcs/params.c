/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 18:08:52 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/28 03:12:39 by lgaveria         ###   ########.fr       */
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

int			is_direct(char *s, t_inst *cur, int param)
{
	int	i;
	int	count;

	if (!s || s[0] != DIRECT_CHAR)
		return (0);
	i = 1;
	if (s[i] && s[i] == LABEL_CHAR)
	{
		while (s[++i] && is_label_chars(s[i]))
			count ++;
		if (count == 0 || s[i])
			return (0);
		(cur->lab_name)[param] = ft_strsub(s, 2, count);
		return (T_LAB);
	}
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (0);
	return (T_DIR);
}

int			is_index(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] || i == 0)
		return (0);
	return (T_IND);
}

int			is_registre(char *s, t_op *op, int p)
{
	int i;

	if (!s || s[0] != 'r')
		return (0);
	i = 1;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] || i == 1)
		return (0);
	printf("\n|%s| numero %d\n\n", s, p);//
	op->params[p] = itohex(ft_atoi(&(s[1])), 1);
	op->psize[p] = 1;
	return (T_REG);
}

int			par_type(char *s, t_inst *cur, int p)
{
	int	i;
	int	ret;

	i = 0;
	if (s[i] == ' ')
		i++;
	if ((ret = is_direct(&(s[i]), cur, p)))
	{
		if (ret == T_DIR)
			(cur->op->params)[p] = itohex(ft_atoi(&(s[i + 1])), cur->op->d_siz);
		cur->op->psize[p] = cur->op->d_siz;
	}
	else if ((ret = is_index(&(s[i]))))
	{
		cur->op->params[p] = itohex(ft_atoi(&(s[i])), 2);
		cur->op->psize[p] = 2;
	}
	else if ((ret = is_registre(&(s[i]), cur->op, p)))
		return (T_REG);
	else
		return (0);
	return (ret);
}
