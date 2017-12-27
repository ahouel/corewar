/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:56:42 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/18 19:56:10 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

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

static t_champ	*select_fun(char *s, int i, t_champ *pl)
{
	t_champ	*(*funptr[15])(t_champ*, char*);

	funptr[0] = &make_live;
	//a poursuivre
	return (funptr[i](pl, s));
}

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

t_champ			*do_parsing(t_champ *champ, char **input, int i)
{
	int		j;

	while (input[++i])
	{
		j = 0;
		while (j != -1 && input[i][j])
		{
			if (input[i][j] == COMMENT_CHAR)
				j = -1;
			else if (get_instruction(&(input[i][j]), champ))
				j = -1;
			else if (how_many_label_char(&(input[i][j])))
			{
				champ = new_label(&(input[i][j]), champ);
				j += how_many_label_char(&(input[i][j])) + 1;
			}
		}
	}
	return (champ);
}
