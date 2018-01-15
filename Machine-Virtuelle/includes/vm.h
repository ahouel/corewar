/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:56:25 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/15 12:48:07 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <ncurses.h>

# include "libft.h"
# include "op.h"
# include "vm_struct.h"

/*
**	--------INITIALIZATION-------
*/

void		initialisation(t_vm *vm);
void		init_vm(t_vm *vm);
int			check_arg(t_vm *vm, int ac, char **av);
int			srch_player(t_vm *vm, int ac, char **av, int *i);
void		error(t_vm *vm, char *str);
void		write_players(t_vm *vm, int nb, int num);
void		new_player(t_vm *vm, int nb, char *str);
void		swap_players(t_vm *vm, int nb, char *str);
int			get_winner(t_vm *vm);
void		free_vm(t_vm *vm);

/*
**	----------EXECUTION-----------
*/

void		exe(t_vm *vm);
t_pcb		*create_processus(t_vm *vm, int num);
//void		add_processus(t_vm *vm, t_pcb *proc);
void		move_processus(t_vm *vm, t_pcb *proc);
void		load_op(t_vm *vm, t_pcb *proc);
int			ocp_is_valid(t_vm *vm, t_pcb *proc, unsigned char ocp);
int			get_ind_value(t_vm *vm, int addr);
int			get_address(t_vm *vm, t_pcb *proc, int addr);
void		print_ram(t_vm *vm);
//int			valid_regs(t_pcb *proc);
void		store_ind_value(t_vm *vm, int addr, int value, int p);

/*
**	--------INSTRUCTIONS----------
*/

void		live(t_vm *vm, t_pcb *proc);
void		ld(t_vm *vm, t_pcb *proc);
void		st(t_vm *vm, t_pcb *proc);
void		add(t_vm *vm, t_pcb *proc);
void		sub(t_vm *vm, t_pcb *proc);
void		gates(t_vm *vm, t_pcb *proc);
void		zjmp(t_vm *vm, t_pcb *proc);
void		ldi(t_vm *vm, t_pcb *proc);
void		sti(t_vm *vm, t_pcb *proc);
void		ft_fork(t_vm *vm, t_pcb *proc);

/*
**	--------NCURSES---------
*/

void		call_ncurses(t_vm *vm);
void		init_ncurses(WINDOW **w);
void		controller(t_vm *vm);
void		colors_init(t_vm *vm);

/*
**	-------DEBUG-------
*/

void		show_mem_2(t_vm *vm);
void		show_proc_nb(t_vm *vm);
void		debug_display_proc(t_vm *vm);
void		show_players(t_vm *vm);
void		show_processus(t_vm *vm);
void		show_ops(t_vm *vm);

#endif
