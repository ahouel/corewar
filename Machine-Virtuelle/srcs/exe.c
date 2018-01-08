/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:19:04 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/08 18:33:42 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Free le pcb et relink la liste chainee sans ce maillon
*/

static void	delete_processus(t_vm *vm, t_pcb *proc)
{
	t_pcb	*tmp;

//	ft_printf("%{BLUE}p\n", proc);
	if (vm->proc_lst->next == NULL)
		vm->proc_lst = NULL;
	else if (vm->proc_lst == proc)
		vm->proc_lst = proc->next;
	else // (proc && vm->proc_lst)
	{
//		ft_printf("%{RED}s\n", "11111111111");
		tmp = vm->proc_lst;
//		ft_printf("%{RED}s\n", "222222222");
		while (tmp->next)
		{
			if (tmp->next == proc)
			{
				tmp->next = proc->next;
				break ;
			}
			tmp = tmp->next;
		}
//		ft_printf("%{RED}s\n", "33333333333333333");
	}
	if (proc->op)
		free(proc->op);
	free(proc);
	proc = NULL;
}

/*
**	Verifie si les processus ont call live depuis le dernier call
**	de la fonction. Si ce n'est pas le cas : delete le processus.
**	Changement du CTD si NBR_LIVE calls de live ont ete faits
**	Reset les compteurs de vie des joueurs
*/

static void	ctd_manager(t_vm *vm)
{
	t_pcb	*proc;
	t_pcb	*tmp;
	int		i;
	int		lives;

	i = -1;
	lives = 0;
	proc = vm->proc_lst;
	while (proc)
	{
		tmp = proc->next;
		if (vm->cycle - proc->last_live > vm->ctd - 1)
		{
			if (vm->verbosity & 8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
						proc->pid, vm->cycle - proc->last_live, vm->ctd);
//			ft_printf("%{RED}s\n", "BBL");
			delete_processus(vm, proc);
		}
		proc = tmp;
	}
	while (++i < vm->nb_player)
	{
		lives += vm->player[i].lives_count;
		vm->player[i].lives_count = 0;
	}
	if (lives > NBR_LIVE - 1 || vm->last_ctd_decay + (MAX_CHECKS * vm->ctd) < vm->cycle + 1)
	{
		vm->last_ctd_decay = vm->cycle;
		vm->ctd -= CYCLE_DELTA;
		if (vm->verbosity & 2 && vm->proc_lst)
			ft_printf("Cycle to die is now %d\n", vm->ctd);
	}
	if (vm->ctd > 0)
		vm->next_ctd += vm->ctd;
	else
		vm->next_ctd = 0;
}

/*
**	Execution de la vm tant qu'un processus est en vie
*/

void		exe(t_vm *vm)
{
	t_pcb	*proc;

	while (vm->proc_lst)
	{
		++vm->cycle;
		if (2 & vm->verbosity)
			ft_printf("It is now cycle %d\n", vm->cycle);
		if (vm->cycle == vm->next_ctd || !vm->next_ctd)
			ctd_manager(vm);
		if (vm->ncurses)
		{
			call_ncurses(vm);
			controller(vm);
			usleep(vm->delay);
		}
		proc = vm->proc_lst;
		while (proc)
		{
			move_processus(vm, proc);
			proc = proc->next;
		}
		if (!vm->ncurses && vm->cycle == vm->dump)
		{
			print_ram(vm);
			free_vm(vm);
			exit(EXIT_SUCCESS);
		}
	}
}
