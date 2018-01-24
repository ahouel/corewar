/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itohex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 17:15:59 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/24 15:48:00 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char		*itohex(int n, int size)
{
	char			*ret;
	int				i;

	printf("\nITOHEX\n__________\nn = %d\n", n);
	if (!(ret = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ret[size] = '\0';
	while (--size >= 0)
	{
		ret[size] = n % 256;
		n /= 256;
	}
	return (ret);
}
