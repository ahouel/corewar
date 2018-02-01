/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 18:08:52 by lgaveria          #+#    #+#             */
/*   Updated: 2018/02/01 14:10:06 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	is_direct(char *s, t_inst *cur, int param, t_champ *pl)
{
	int	i;
	int	count;

	if (!s || s[0] != DIRECT_CHAR)
		return (0);
	i = 1;
	if (s[i] && s[i] == LABEL_CHAR)
	{
		count = 0;
		while (s[++i] && is_label_char(s[i], pl))
			count++;
		if (count == 0 || (s[i] && (s[i] != ' ' || s[i + 1])))
			exit_free("wrong parameter format at line ", pl, pl->t, cur->line);
		(cur->lab_name)[param] = ft_strsub(s, 2, count);
		return (T_LAB);
	}
	else if (s[i] == '0' || ft_atoi(&(s[i++])))
	{
		while (s[i] && ft_isdigit(s[i]))
			i++;
		if (s[i] && (s[i] != ' ' || s[i + 1]))
			exit_free("wrong parameter format at line ", pl, pl->t, cur->line);
		return (T_DIR);
	}
	return (0);
}

static int	is_index(char *s, t_inst *cur, int param, t_champ *pl)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	i = 0;
	if (s[i] && s[i] == LABEL_CHAR)
	{
		count = 0;
		while (s[++i] && is_label_char(s[i], pl))
			count++;
		if (count == 0 || s[i])
			exit_free("wrong parameter format at line ", pl, pl->t, cur->line);
		(cur->lab_name)[param] = ft_strsub(s, 1, count);
		return (T_ILAB);
	}
	else if (s[i] == '0' || ft_atoi(&(s[i++])))
	{
		while (s[i] && ft_isdigit(s[i]))
			i++;
		if ((s[i] && (s[i] != ' ' || s[i + 1])))
			exit_free("wrong parameter format at line ", pl, pl->t, cur->line);
		return (T_IND);
	}
	return (0);
}

static int	is_registre(char *s, t_op *op, int p)
{
	int i;

	if (!s || s[0] != 'r')
		return (0);
	i = 1;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if ((s[i] && (s[i] != ' ' || s[i + 1])) || i == 1)
		return (0);
	op->params[p] = itohex(ft_atoi(&(s[1])), 1);
	op->psize[p] = 1;
	return (T_REG);
}

int			par_type(char *s, t_inst *cur, int p, t_champ *pl)
{
	int	i;
	int	ret;

	i = 0;
	if (s[i] == ' ')
		i++;
	if ((ret = is_direct(&(s[i]), cur, p, pl)))
	{
		if (ret == T_DIR)
			cur->op->params[p] = itohex(ft_atoi(&(s[++i])), cur->op->dir_size);
		cur->op->psize[p] = cur->op->dir_size;
	}
	else if ((ret = is_index(&(s[i]), cur, p, pl)))
	{
		if (ret == T_IND)
			cur->op->params[p] = itohex(ft_atoi(&(s[i])), 2);
		cur->op->psize[p] = 2;
	}
	else if ((ret = is_registre(&(s[i]), cur->op, p)))
		return (T_REG);
	else
		return (0);
	return (ret);
}
