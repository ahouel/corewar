/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 21:21:43 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/27 23:19:59 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	free_op(t_op *op)
{
	int	i;

	if (op->params)
	{
		i = 0;
		while (i < 3)
		{
			if (op->params[i])
				free(op->params[i]);
				i++;
		}
	}
	op->name = NULL;
	free(op);
	op = NULL;
}
