/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:21:24 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 16:19:59 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_ocp(t_vm *vm, t_pcb *proc)
{
	if (op_tab[proc->op->code - 1].need_ocp)
	{
		proc->pc++;
		proc->op->ocp = vm->ram[proc->pc].mem;
	}
}

void	get_dir(t_vm *vm, t_pcb *proc, int num)
{
	unsigned int value;

	value = 0;

	proc->pc++;

	value = (unsigned char)vm->ram[proc->pc].mem;
	if (vm->debug)
		printf("Value => %x\n", value);
	if (vm->debug)
	printf("Pc => %d\n", proc->pc);
	proc->pc++;
	value = value << 8;
	if (proc->pc > MEM_SIZE)
		return ;		// FIXXXXX
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	if (vm->debug)
	printf("Value => %x\n", value);
	if (vm->debug)
	printf("Pc => %d\n", proc->pc);

	if (op_tab[proc->op->code - 1].direct_size)
	{
		if ((value & 0x8000) == 0x8000)
			value = (value - USHRT_MAX) - 1;
		proc->op->ar[num] = value;
		return ;
	}

	if (proc->op->code == 1 && proc->pid == 5 && vm->debug)
		printf("GET DIR 4\n");
	proc->pc++;
	value = value << 8;
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	proc->pc++;
	value = value << 8;
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	proc->op->ar[num] = value;
	if (proc->op->code == 1 && proc->pid == 5 && vm->debug)
		printf("live value => %d   arg_num => %d\n", value, num);
}

void	get_reg(t_vm *vm, t_pcb *proc, int num)
{
	unsigned char value;

	proc->pc++;
	value = (unsigned char)vm->ram[proc->pc].mem;
	proc->op->ar[num] = value;
}

void	get_ind(t_vm *vm, t_pcb *proc, int num)
{
	// printf(">>>>>>>>>>GET_IND<<<<<<<<<<<\n");

	unsigned int value;

	value = 0;

	proc->pc++;
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	proc->pc++;
	value = value << 8;
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	proc->op->ar[num] = value;
	if ((value & 0x8000) == 0x8000)
	 	proc->op->ar[num] = (value - USHRT_MAX) - 1;
}

void	find_args(t_vm *vm, t_pcb *proc, int num)
{
	// printf("ENTER FUNC : FIND_ARGS\n");
	unsigned char	type;
	unsigned char	mask;

	type = proc->op->ocp;
	mask = 0xC0;
	mask = mask >> (2 * num);
	type = type & mask;
	type = type >> (6 - 2 * num);
	proc->op->ar_typ[num] = type;

	if (proc->op->code == 1)
		printf("LIVE OP CODE\n");

	if (type == REG_CODE)
		get_reg(vm, proc, num);
	if (type == DIR_CODE)
		get_dir(vm, proc, num);
	if (type == IND_CODE)
		get_ind(vm, proc, num);
}

int		is_opcode(char data)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if ((char)op_tab[i].code == data)
			return (data);
		i++;
	}
	return (0);
}

int		count_pcb(t_vm *vm)
{
	int i;
	t_pcb	*proc;

	i = 0;
	proc = vm->proc;
	while (proc)
	{
		if (proc->state == 'R')
			i++;
		proc = proc->next;
	}
	return (i);
}

int		modulo(int a, int b)
{
	if (a % b >= 0)
		return (a % b);
	else
		return ((a % b) + b);
	// return (a % b) >= 0 ? (a % b) : (a % b) + b;
}

static int	get_winner(t_vm *vm)
{
	int i;
	int best;


	i = 1;
	best = 1;
	while (i < vm->nb_player)
	{
		if (vm->player[i].last_live < vm->player[best].last_live)
			best = i;
		i++;
	}
	return (best);
}

static void	init_vm(t_vm *vm)
{
	vm->nb_player = 0;
//	vm->lives_in_cycle = 0;
	vm->ctd = CYCLE_TO_DIE;
	vm->cycle = 0;
	vm->proc = NULL;
	vm->last_one = NULL;
	vm->pause = 1;
	vm->ncurses = 0;
	vm->delay = NCURSES_DELAY;
	vm->ctd_check = 0;
	vm->next_ctd = CYCLE_TO_DIE;
	vm->dump = -1;
	vm->debug = 0;
}

int		main(int argc, char **argv)
{
	t_vm	vm;
	WINDOW *w;

	init_vm(&vm);
	if(check_arg(&vm, argc, argv))
		error("Error\n");
	if (vm.ncurses)
		init_ncurses(&w);
	ft_printf("%d\n", vm.nb_player);
	initialisation(&vm);
	ft_printf("=======FIGHT=======\n");
	//ft_printf("verbo : %d", vm.verbosity);
	exe(&vm);
	if (vm.ncurses)
		endwin();
	printf("winner nb -> %d\n", get_winner(&vm));
	return (0);
}
