/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 21:10:01 by lgaveria          #+#    #+#             */
/*   Updated: 2018/02/01 15:39:30 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		free_tab(char **tab)
{
	int		i;

	if (!tab)
		return ;
	i = ft_tablen(tab);
	while (--i >= 0)
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}
