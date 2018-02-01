/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 21:19:53 by lgaveria          #+#    #+#             */
/*   Updated: 2018/02/01 15:09:18 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	free_instructions(t_inst *lst)
{
	int		i;

	if (lst->op)
		free_op(lst->op);
	lst->op = NULL;
	i = 0;
	while (i < 3)
	{
		if (lst->lab_name[i])
			free(lst->lab_name[i]);
		i++;
	}
	if (lst->next)
	{
		free_instructions(lst->next);
		lst->next = NULL;
	}
	free(lst);
	lst = NULL;
}
