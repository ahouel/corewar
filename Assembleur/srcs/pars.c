/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:56:42 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/06 19:14:37 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	Cette fonction sera dégagée dès que j'aurais intégré la structure présente
**	dans op.c.
*/

static char		**init_instruction_tab(void)
{
	char	**tab;

	if (!(tab = malloc(sizeof(char*) * 17)))
		return (NULL); // ATTENTION
	tab[0] = ft_strdup("live");
	tab[1] = ft_strdup("ldi");
	tab[2] = ft_strdup("sti");
	tab[3] = ft_strdup("add");
	tab[4] = ft_strdup("sub");
	tab[5] = ft_strdup("and");
	tab[6] = ft_strdup("or");
	tab[7] = ft_strdup("xor");
	tab[8] = ft_strdup("zjmp");
	tab[9] = ft_strdup("ld");
	tab[10] = ft_strdup("st");
	tab[11] = ft_strdup("fork");
	tab[12] = ft_strdup("lldi");
	tab[13] = ft_strdup("lld");
	tab[14] = ft_strdup("lfork");
	tab[15] = ft_strdup("aff");
	tab[16] = NULL;
	return (tab);
}

/*
**	On récupère la ligne à traiter, ainsi que l'index de l'instruction
**	correspondante dans le tableau, et notre structure générale.
**	Le tableau de pointeur sur fonction est initialisé, et on retourne l'appelle
**	à la fonction correspondante.
**	??? Remplacer ce pointeur sur fonction par un nouvel élément dans la
**	structure d'op.c ?
*/

static t_champ	*select_fun(char *s, int i, t_champ *pl)
{
	t_champ	*(*funptr[15])(t_champ*, char*);

	funptr[0] = &make_live;
	funptr[1] = NULL;
	funptr[2] = &make_sti;
	funptr[3] = NULL;
	funptr[4] = NULL;
	funptr[5] = &make_and;
	funptr[6] = NULL;
	funptr[7] = NULL;
	funptr[8] = NULL;
	funptr[9] = NULL;
	funptr[10] = NULL;
	funptr[11] = NULL;
	funptr[12] = NULL;
	funptr[13] = NULL;
	funptr[14] = NULL;
	if (!funptr[i])
	{
		new_instruction(s, &pl);
		return (pl);
	}
	return (funptr[i](pl, s));
}

/*
**	On avance dans la ligne jusqu'à une potentielle instruction et on intialise
**	le tableau avec tous les termes. La couple compare notre ligne avec chacuns
**	et s'il y a correspondance, on appelle select_fun qui s'occupera de traiter
**	l'instruction.
*/

static int		get_instruction(char *s, t_champ *pl)
{
	char	**to_compare;
	int		i;
	int		ret;

	i = 0;
	while (ft_iswhitespace(s[i]))
		i++;
	s = &(s[i]);
	to_compare = init_instruction_tab();
	i = -1;
	ret = 0;
	while (to_compare[++i] && ret == 0)
		if (ft_strncmp(s, to_compare[i], ft_strlen(to_compare[i])) == 0)
			if (ft_iswhitespace(s[ft_strlen(to_compare[i])]))
			{
				select_fun(s, i, pl);
				ret = 1;
			}
	free_tab(to_compare);
	return (ret);
}

/*
**	On parcourt le tableau selon 3 conditions : 
**		-si on arrive sur un commentaire, on passe à la ligne suivante;
**		-si on tombe sur une instruction, elle sera traitée depuis la fonction
**			qui l'identifie;
*		-si on lit un label, on le place dans notre liste chainée puis on avance
*			dans la ligne jusqu'à la fin de ce label.
*/

t_champ			*do_parsing(t_champ *pl, char **input, int i)
{
	int		j;

	while (input[++i])
	{
		j = 0;
		while (j != -1 && input[i][j])
		{
			if (input[i][j] == COMMENT_CHAR)
				j = -1;
			else if (get_instruction(&(input[i][j]), pl))
				j = -1;
			else if (how_many_label_char(&(input[i][j])))
			{
				pl = new_label(&(input[i][j]), pl);
				j += how_many_label_char(&(input[i][j])) + 1;
			}
		}
	}
	pl = get_labels_params(pl);
	return (pl);
}
