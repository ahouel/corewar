/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 21:19:53 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/27 23:20:03 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	free_instructions(t_inst *lst)
{
	if (lst->op)
		free(lst->op);
	lst->op = NULL;
	if (lst->next)
	{
		free_instructions(lst->next);
		lst->next = NULL;
	}
	free(lst);
	lst = NULL;
}
