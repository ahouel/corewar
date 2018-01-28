/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itohex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 17:15:59 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/28 02:59:11 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char		*itohex(int n, int size)
{
	char			*ret;

	if (!(ret = ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	printf("ITOHEX [%d] ->", n);
	while (--size >= 0)
	{
		ret[size] = n % 256;
		n /= 256;
	}
	printf("|%s| size = %zu\n", ret, ft_strlen(ret));
	if (ret[0] == 1)
		printf("-_-_-_ YOUHOU _-_-_-\n");
	return (ret);
}
