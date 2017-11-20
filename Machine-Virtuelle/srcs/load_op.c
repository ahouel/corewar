/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:22:35 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/20 16:14:31 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_dir(t_vm *vm, t_pcb *proc, int num)
{
	unsigned int value;

	value = 0;

	proc->pc++;

	value = (unsigned char)vm->ram[proc->pc].mem;
	if (vm->debug != -1)
		printf("Value => %x\n", value);
	if (vm->debug != -1)
		printf("Pc => %d\n", proc->pc);
	proc->pc++;
	value = value << 8;
	if (proc->pc > MEM_SIZE)
		return ;		// FIXXXXX
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	if (vm->debug > -1)
		printf("Value => %x\n", value);
	if (vm->debug > -1)
		printf("Pc => %d\n", proc->pc);

	if (op_tab[proc->op->code - 1].nb_byte)
	{
		if ((value & 0x8000) == 0x8000)
			value = (value - USHRT_MAX) - 1;
		proc->op->ocp[num] = value;
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
	proc->op->ocp[num] = value;
	if (proc->op->code == 1 && proc->pid == 5 && vm->debug)
		printf("live value => %d   arg_num => %d\n", value, num);
}

void	get_reg(t_vm *vm, t_pcb *proc, int num)
{
	unsigned char value;

	proc->pc++;
	value = (unsigned char)vm->ram[proc->pc].mem;
	proc->op->ocp[num] = value;
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
	proc->op->ocp[num] = value;
	if ((value & 0x8000) == 0x8000)
		proc->op->ocp[num] = (value - USHRT_MAX) - 1;
}

void	find_args(t_vm *vm, t_pcb *proc, int num)
{
	// printf("ENTER FUNC : FIND_ARGS\n");
	unsigned char	type;
	unsigned char	mask;

	ft_printf("%02x\n", vm->ram[(proc->pc + 1) % MEM_SIZE].mem);
	type = vm->ram[(proc->pc + 1) % MEM_SIZE].mem;
	ft_printf("%{RED}0b\n", type);
	mask = 0xC0;
	mask = mask >> (2 * num);
	type = type & mask;
	type = type >> (6 - 2 * num);
//	ft_printf("%#{RED}d", type);
	if (proc->op->code == 1)
		printf("LIVE OP CODE\n");
	if (type == REG_CODE)
		get_reg(vm, proc, num);
	if (type == DIR_CODE)
		get_dir(vm, proc, num);
	if (type == IND_CODE)
		get_ind(vm, proc, num);
}

void	load_op(t_vm *vm, t_pcb *proc)
{
	int i;
	t_op *op;
	unsigned char ocp;

	i = -1;
	if (proc->op->has_ocp)
	{
		ft_printf("%{BLUE}02x\n", proc->pc);
		proc->pc++; 
		while (++i < op_tab[proc->op->code - 1].nb_arg)
		{
			find_args(vm, proc, i);
		}
		op = proc->op;
		ft_printf("inst : %s, nb arg : %d, code : %d, has ocp : %d, nb_byte : %d\nresult : ocp0 : %x, ocp1 : %x, ocp2 : %x\n", op->inst, op->nb_arg, op->code, op->has_ocp, op->nb_byte, op->ocp[0], op->ocp[1], op->ocp[2]);
	}
	else
	{
		get_dir(vm, proc, 0);
	}
	proc->pc++;
}
