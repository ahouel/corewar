/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srch_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:23:22 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/11 14:42:27 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	On cherche s'il y a un -n et on renvois le nombre apres
*/

static int	srch_nb_player(t_vm *vm, int ac, char **av, int *i)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(av[*i], "-n"))
	{
		if (*i + 2 < ac && ft_str_isdigit(av[*i + 1]))
		{
			ret = ft_atoi(av[*i + 1]);
			if (ret > 0 && ret < MAX_PLAYERS + 1)
			{
				(*i) += 2;
				return (ret - 1);
			}
		}
		error(vm, "-n wrong number");
	}
	return (-1);
}

/*
**	Recherche un -n si il y en a, puis le .cor
*/

int			srch_player(t_vm *vm, int ac, char **av, int *i)
{
	int		nb;
	char	*tmp;

	nb = srch_nb_player(vm, ac, av, i);
	if ((tmp = ft_strstr(av[*i], ".cor")) && !tmp[4] && ft_strlen(av[*i]) > 4)
	{
		vm->nb_player++;
		if (vm->nb_player > MAX_PLAYERS)
			error(vm, "too many champs");
		new_player(vm, nb, av[*i]);
		return (1);
	}
	return (0);
}
