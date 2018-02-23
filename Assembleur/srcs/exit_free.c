/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:49 by ahouel            #+#    #+#             */
/*   Updated: 2018/02/16 16:32:11 by gbradel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		exit_free(char *str, t_champ *pl, char **tab, int line)
{
	ft_printf("%{MAGENTA}s", "error: ");
	if (line)
		ft_printf(str, line);
	else
		ft_printf("%{RED}s\n", str);
	if (tab)
		free_tab(tab);
	if (pl)
		free_champ(pl);
	exit(EXIT_FAILURE);
}
