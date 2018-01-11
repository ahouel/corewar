/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ocp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 19:07:57 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/06 19:10:04 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	get_ocp(t_inst *current)
{
	char ocp;

	ocp = current->size_one[1] * 64;
	ocp += current->size_two[1] * 16;
	ocp += current->size_three[1] * 4;
	return (ocp);
}
