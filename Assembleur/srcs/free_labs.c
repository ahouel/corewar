/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_labs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 21:17:20 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/27 23:17:56 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		free_labs(t_lab *lab)
{
	if (lab->name)
		free(lab->name);
	lab->name = NULL;
	if (lab->lst)
		free_instructions(lab->lst);
	if (lab->next)
	{
		free_labs(lab->next);
		lab->next = NULL;
	}
	free(lab);
	lab = NULL;
}
