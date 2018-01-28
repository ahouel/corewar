/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:56:42 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/28 06:57:31 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void		get_params(t_champ *pl, char *s, int i, int line)
{
	t_inst	*new;
	char	**tab;
	int		j;

	new = new_instruction(pl, i, line);
	j = ft_strlen(new->op->name);
	while (ft_iswhitespace(s[j]))
		j++;
	tab = ft_strsplit(&(s[j]), SEPARATOR_CHAR);
	if (ft_tablen(tab) != new->op->nb_param)
		exit_free("instruction wrong usage at the line ", pl, line);
	j = 0;
	while (tab[j])
	{
		new->op->p_type[j] = new->op->p_type[j] & par_type(tab[j], new, j);
		if (!(new->op->p_type)[j])
			exit_free("wrong parametre at the line ", pl, line);
		j++;
	}
	new->op->size += new->op->psize[0] + new->op->psize[1] + new->op->psize[2];
	if (new->op->ocp)
		new->op->size += 1;
//	printf("PC = %d [%s]\n", pl->current_pc, s);
	pl->current_pc += new->op->size;
}

/*
**	On recupere le premier mot de la string puis on le compare avec le nom de
**	chaque instruction presente dans op_tab. On renvoit le tout get_params qui
**	accedera au parsing et recuperera les information necessaires.
*/

static char		get_instruction(char *s, t_champ *pl, int line)
{
	char	**to_compare;
	int		len;
	int		i;
	char	*tmp;

	len = 0;
	while (s[len] && ft_iswhitespace(s[len]))
		len++;
	s = &(s[len]);
	len = 0;
	while (s[len] && ft_isalpha(s[len]))
		len++;
	if (s[len] == LABEL_CHAR)
		return (0);
	tmp = ft_strsub(s, 0, len);
	i = 0;
	while ((op_tab[i]).name && ft_strcmp(tmp, (op_tab[i]).name) != 0)
		i++;
	free(tmp);
	if ((op_tab[i]).name)
		get_params(pl, s, i, line);
	return ((op_tab[i]).opcode);
}

/*
**	On parcourt le tableau selon 3 conditions : 
**		-si on arrive sur un commentaire, on passe à la ligne suivante;
**		-si on tombe sur une instruction, elle sera traitée depuis la fonction
**			qui l'identifie et on passe a la ligne suivante;
**		-si on lit un label, on le place dans notre liste chainée puis on avance
*			dans la ligne jusqu'à la fin de ce label.
*/

t_champ			*do_parsing(t_champ *pl, int i)
{
	int		j;

	while ((pl->input)[++i])
	{
		j = 0;
		while (j != -1 && (pl->input)[i][j])
		{
			if ((pl->input[i][j]) == COMMENT_CHAR)
				j = -1;
			else if (get_instruction(&((pl->input)[i][j]), pl, i - 1))
				j = -1;
			else if (how_many_label_char(&((pl->input)[i][j])))
			{
				pl = new_label(&((pl->input)[i][j]), pl);
				j += how_many_label_char(&((pl->input)[i][j])) + 1;
				while ((pl->input)[i][j] && ft_iswhitespace((pl->input)[i][j]))
					j++;
			}
			else if (pl->input[i])
				exit_free("wrong input at the line ", pl, i);
		}
	}
	return (fill_label_params(pl));
}
