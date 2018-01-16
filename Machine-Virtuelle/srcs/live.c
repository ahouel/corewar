/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:20:53 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/16 17:57:11 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Change le timer live de la case de l'op pour
**	la surbrillance sur ncurse
*/

static void	set_live_case(t_vm *vm, t_pcb *proc)
{
	int	pc;

	pc = proc->pc - 5;
	while (pc < 0)
		pc += MEM_SIZE;
	vm->ram[pc % MEM_SIZE].live = LIVE_FLASH;
}

/*
**	Ecrit si un joueur est reporte comme etant en vie avec -v 1
*/

static void	print_live(t_vm *vm, t_pcb *proc, int i)
{
	if (vm->verbosity & V_LIVES)
		ft_printf("Player %d (%s) is said to be alive\n", i,
				vm->player[i - 1].name);
}

/*
**	Rapporte le joueur designe par le param comme etant en vie
**	(- num du joueur)
*/

void		live(t_vm *vm, t_pcb *proc)
{
	int	i;

	i = proc->op->param[0];
	proc->last_live = vm->cycle;
	if (vm->verbosity & V_OP)
		ft_printf("%d\n", i);
	i = -i;
	vm->period_lives++;
	if (i < 1 || i > MAX_PLAYERS)
		return ;
	if (!vm->player[i - 1].active)
		return ;
	vm->player[i - 1].lives_count++;
	vm->player[i - 1].last_live = vm->cycle;
	print_live(vm, proc, i);
	if (vm->ncurses)
		set_live_case(vm, proc);
}
