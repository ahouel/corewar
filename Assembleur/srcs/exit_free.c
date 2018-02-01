/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:49 by ahouel            #+#    #+#             */
/*   Updated: 2018/02/01 15:42:31 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		exit_free(char *str, t_champ *pl, char **tab, int line)
{
	ft_putstr("error: ");
	ft_putstr(str);
	if (line)
	{
		ft_putnbr(line);
		write(1, "\n", 1);
	}
	if (tab)
		free_tab(tab);
	if (!tab && pl->t)
	{
		if (pl->t[0])
			free_tab(pl->t);
	}
	if (pl)
		free_champ(pl);
	exit(EXIT_FAILURE);
}
