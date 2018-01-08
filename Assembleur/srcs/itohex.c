/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itohex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 17:15:59 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/06 16:41:12 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char		*itohex(int n, int size)
{
	char			*ret;
	int				i;

	if (!(ret = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ret[size] = '\0';
	while (--size >= 0)
	{
		ret[size] = n % 16;
		n /= 16;
	}
	return (ret);
}
