/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 21:13:46 by lgaveria          #+#    #+#             */
/*   Updated: 2018/02/01 14:13:36 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		free_champ(t_champ *champ)
{
	if (champ->input)
		free_tab((champ->input));
	if (champ->head)
		free(champ->head);
	champ->head = NULL;
	if (champ->lab)
		free_labs(champ->lab);
	free(champ);
	champ = NULL;
}
