/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:49 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/02 14:40:11 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	En cas d error afficher str et exit le programme
*/

void	free_instructions(t_inst *lst)
{
	if (lst->next)
	{
		free_instructions(lst->next);
		lst->next = NULL;
	}
	if (lst->param_one)
		free(lst->param_one);
	if (lst->param_two)
		free(lst->param_two);
	if (lst->param_three)
		free(lst->param_three);
	if (lst->name)
		free(lst->name);
	free(lst);
	lst = NULL;
}

void	free_labs(t_lab *lab)
{
	if (lab->next)
	{
		free_labs(lab->next);
		lab->next = NULL;
	}
	if (lab->lst)
		free_instructions(lab->lst);
	if (lab->name)
		free(lab->name);
	free(lab);
	lab = NULL;
}

void	free_champ(t_champ *champ)
{
	if (champ->head)
		free((champ->head));
	champ->head = NULL;
	free(champ);
	champ = NULL;
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	exit_free(char *str, t_champ *champ, char **input)
{
	ft_putstr(str);
	free_champ(champ);
	free_tab(input);
	exit(EXIT_FAILURE);
}
