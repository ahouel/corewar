/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:49:49 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/24 18:17:06 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
** !! Manque la gestion d'erreur sur des entrees pas exa correctes.
**
** Le premier parametre est un registre, un direct de taille 2 ou un index.
** Les trois posssibilites sont verifiees, on rentre dans param_one la valeur
** qui finira dans le .cor octet par octet.
** Size_one[0] correspond a la taille du parametre en octet.
** Size_one[1] correspond a la valeur de ce parametre pour l'OCP.
** On renvoit la taille du parametre.
*/

static int	get_first_param(char *s, t_inst *new, t_champ *pl)
{
	int tmp;

	if (s[0] == 'r' && ft_isdigit(s[1]))
	{
		new->param_one = itohex(ft_atoi(&(s[1])), 1);
		new->size_one[0] = 1;
		new->size_one[1] = 1;
	}
	else if ((tmp = is_direct(s, pl, 1, new)))
	{
		new->size_one[0] = 2;
		new->size_one[0] = 2;
		if (tmp == 1)
			new->param_one = itohex(ft_atoi(&(s[1])), 2);
	}
	else if (ft_atoi(s))
	{
		new->param_one = itohex(ft_atoi(s), 2);
		new->size_one[0] = 2;
		new->size_one[1] = 3;
	}
	return (new->size_one[0]);
}

/*
** Idem, mais il s'agit cette fois d'un direct 2o ou d'un registre.
*/

static int	get_second_param(char *s, t_inst *new, t_champ *pl)
{
	int tmp;
	int i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i] == 'r' && ft_isdigit(s[i + 1]))
	{
		new->param_two = itohex(ft_atoi(&(s[i + 1])), 1);
		new->size_two[0] = 1;
		new->size_two[1] = 1;
	}
	else if ((tmp = is_direct(&(s[i]), pl, 2, new)))
	{
		new->size_two[0] = 2;
		new->size_two[1] = 2;
		if (tmp == 1)
			new->param_two = itohex(ft_atoi(&(s[i + 1])), 2);
	}
	return (new->size_two[0]);
}

/*
** Le dernier parametre ne peut etre qu'un registre.
*/

static int	get_third_param(char *s, t_inst *new)
{
	int i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i++] != 'r' || !(ft_isdigit(s[i])))
		return (0);
	new->param_three = itohex(ft_atoi(&(s[i])), 1);
	new->size_three[0] = 1;
	new->size_three[1] = 1;
	return (1);
}

/*
** (l.114) On saute l'appel de l'instruction dans la string recupere, et on
** decoupe le reste avec un strsplit, de sorte a ne garder qu'un parametre par
** string du tableau.
** (l.115) On controle alors le nombre de parametre. (l.117) S'il y en a 3, On
** creer une nouvelle instruction dans notre liste chainee.
** (l.118) On remplit l'opcode correspondant a ldi.
** (l.119-124) Une par une, on appelle les fonctions correspondant a chaque
** parametre, en s'assurant qu'il y a un retour.
** (l.125-128) On recupere l'ocp, calcule la taille et remet le PC a jour.
*/

t_champ		*make_ldi(t_champ *pl, char *s)
{
	char	**tab;
	t_inst	*new;

	tab = ft_strsplit((char const *)(&(s[3])), SEPARATOR_CHAR);
	if (ft_tablen(tab) != 3)
		return (NULL); //a revoir
	new = (new_instruction("ldi\0", &pl));
	new->opcode = 10;
	if (!(new->size_one[0] = get_first_param(tab[0], new, pl)))
		return (NULL); //a revoir
	if (!(new->size_two[0] = get_second_param(tab[1], new, pl)))
		return (NULL); //a revoir
	if (!(new->size_three[0] = get_third_param(tab[2], new)))
		return (NULL); //a revoir
	new->ocp = get_ocp(new);
	new->size = new->size_one[0] + new->size_two[0] + new->size_three[0] + 2;
	new->pc = pl->current_pc;
	pl->current_pc += new->size;
	return (pl);
}
