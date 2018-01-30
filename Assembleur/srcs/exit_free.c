/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:49 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/29 17:16:28 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		exit_free(char *str, t_champ *pl, int line)
{
	ft_putstr(str);
	if (line)
	{
		ft_putnbr(line + 1);
		write(1, "\n", 1);
	}
	if (pl)
		free_champ(pl);
	exit(EXIT_FAILURE);
}
