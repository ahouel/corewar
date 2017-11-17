/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:56:25 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/17 16:41:54 by ahouel           ###   ########.fr       */
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
# include "ft_printf.h"
# include "op.h"
# include "vm_struct.h"

/*
**	--------INITIALIZATION-------
*/

void		initialisation(t_vm *vm);
int			check_reg(int nb);
int			check_params(t_op *op);
int			check_arg(t_vm *vm, int argc, char **argv);
void		find_args(t_vm *vm, t_pcb *proc, int num);
int			ft_strargv(int argc, char **argv, char *str);
int			srch_players(t_vm *vm, int argc, char **argv);
void		error(char *str);
void		write_players(t_vm *vm, int nb, int num);

/*
**	----------EXECUTION-----------
*/

void		exe(t_vm *vm);
t_pcb		*create_processus(t_vm *vm, int num);
void		add_process(t_vm *vm, t_pcb *proc);
void		wait_state(t_vm *vm, t_pcb *proc);
void		idle_state(t_vm *vm, t_pcb *proc);
t_op		*create_op(t_vm *vm, t_pcb *proc, char data);
void		undertaker(t_vm *vm);
void		kill_proc(t_vm *vm);
void		fill_cur_op(t_vm *vm, t_pcb *proc);
int			is_pc(t_vm *vm, int nb);
int			count_proc(t_vm *vm);
int			all_died(t_vm *vm);
int			is_opcode(char data);
int			cycle_to_die(t_vm *vm);
t_player	*get_survivor(t_vm *vm);
void		get_ocp(t_vm *vm, t_pcb *proc);
void		get_dir(t_vm *vm, t_pcb *proc, int num);
int			modulo(int a, int b);
void		show_operations(t_vm *vm, t_pcb *proc);
void		show_pc_move(t_vm *vm, t_pcb *proc);
void		reduce_ctd(t_vm *vm);
int			process_living(t_vm *vm);
void		set_ctd(t_vm *vm);

/*
**	--------INSTRUCTIONS----------
*/

void		and(t_vm *vm, t_pcb *proc);
void		ld(t_vm *vm, t_pcb *proc);
void		ldi(t_vm *vm, t_pcb *proc);
void		sti(t_vm *vm, t_pcb *proc);
void		live(t_vm *vm, t_pcb *proc);
void		add(t_vm *vm, t_pcb *proc);
void		or(t_vm *vm, t_pcb *proc);
void		xor(t_vm *vm, t_pcb *proc);
void		st(t_vm *vm, t_pcb *proc);
void		sub(t_vm *vm, t_pcb *proc);
void		ft_fork(t_vm *vm, t_pcb *proc);
void		zjmp(t_vm *vm, t_pcb *proc);
void		lld(t_vm *vm, t_pcb *proc);

/*
**	--------NCURSES---------
*/

void		call_ncurses(t_vm *vm);
void		init_ncurses(WINDOW **w);
void		controller(t_vm *vm);

/*
**	-------DEBUG-------
*/

void		show_mem(t_vm *vm);
void		show_mem_2(t_vm *vm);
void		show_proc_nb(t_vm *vm);
void		debug_display_proc(t_vm *vm);
void		show_players(t_vm *vm);
void		show_processus(t_vm *vm);

#endif
