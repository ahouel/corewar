/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:53:48 by rfulop            #+#    #+#             */
/*   Updated: 2017/10/23 21:58:52 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					get_uint32(unsigned char *buff)
{
	return ((*(buff) << 24) | (*(buff + 1) << 16) |
			(*(buff + 2) << 8) | (*(buff + 3)));
}

short				get_uint16(unsigned char *buff)
{
	return ((*(buff) << 8) | (*(buff + 1)));
}
