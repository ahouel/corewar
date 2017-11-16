/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:49 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 11:18:57 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	En cas d error afficher str et exit le programme
*/

void	error(char *str)
{
	ft_putstr(str);
	exit(EXIT_FAILURE);
}
