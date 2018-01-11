/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:49 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/11 14:49:46 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	En cas d'error affiche str et exit le programme
**	Free au prealable ce qui a ete malloc
*/

void	error(t_vm *vm, char *str)
{
	if (*str)
		ft_printf("%{RED}s %{RED}s\n", "Error :", str);
	free_vm(vm);
	exit(EXIT_FAILURE);
}
