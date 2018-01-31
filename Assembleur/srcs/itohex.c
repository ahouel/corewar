/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itohex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 17:15:59 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/30 16:25:56 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char		*itohex(long n, int size)
{
	char			*ret;

	if (!(ret = ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (n == -2147483648)
	{
		ret[0] = (char)128;
		return (ret);
	}
	if (n < 0 && size == 2)
		n = 65536 + n;
	else if (n < 0 && size == 4)
		n = 4294967296 + n;
	while (--size >= 0)
	{
		ret[size] = n % 256;
		n /= 256;
	}
	return (ret);
}
