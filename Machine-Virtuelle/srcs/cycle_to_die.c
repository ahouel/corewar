/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_to_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:25 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:08:47 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* void	reduce_ctd(t_vm *vm)
** {
** 	// printf("BORDEL  %d\n", total_lives(vm));
** 	if (total_lives(vm) >= NBR_LIVE || vm->ctd_check == MAX_CHECKS)
** 	{
** 		// printf("BORDEL\n");
** 		vm->ctd -= CYCLE_DELTA;
** 		vm->ctd_check = 0;
** 		if (2 & vm->verbosity)
** 			printf("Cycle to die is now %d\n", vm->ctd);
** 	}
** 	else
** 		vm->ctd_check++;
**}
*/

void	set_ctd(t_vm *vm)
{
/*
** printf("lives in cycle => %d\n", vm->lives_in_cycle);
*/
//	if (vm->lives_in_cycle >= NBR_LIVE || vm->ctd_check >= MAX_CHECKS)
//	{
//		vm->ctd -= CYCLE_DELTA;
//		vm->ctd_check = 0;
//		if (2 & vm->verbosity)
//			printf("Cycle to die is now %d\n", vm->ctd);
//	}
//	else
//		vm->ctd_check++;
//	vm->lives_in_cycle = 0;
}
