/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:22:35 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/21 18:06:40 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Enregistre la valeur direct dans la structure t_op
**	Recup : 2 Octets si l'op est : 
**	zjmp | ldi | sti | fork | lfork | lldi
**	4 Octets autrement
*/

static void	get_dir(t_vm *vm, t_pcb *proc, int num)
{
	unsigned int value;

	value = 0;

	proc->pc++;

	value = (unsigned char)vm->ram[proc->pc].mem;
	if (vm->debug == 3)
		printf("Value => %x\n", value);
	if (vm->debug == 3)
		printf("Pc => %d\n", proc->pc);
	proc->pc++;
	value = value << 8;
	if (proc->pc > MEM_SIZE)
		return ;		// FIXXXXX
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	if (vm->debug == 3)
		printf("Value => %x\n", value);
	if (vm->debug == 3)
		printf("Pc => %d\n", proc->pc);

	if (op_tab[proc->op->code - 1].nb_byte)
	{
		if ((value & 0x8000) == 0x8000)
			value = (value - USHRT_MAX) - 1;
		proc->op->ocp[num] = value;
		return ;
	}

	if (proc->op->code == 1 && proc->pid == 5 && vm->debug == 3)
		printf("GET DIR 4\n");
	proc->pc++;
	value = value << 8;
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	proc->pc++;
	value = value << 8;
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	proc->op->ocp[num] = value;
	if (proc->op->code == 1 && proc->pid == 5 && vm->debug == 3)
		printf("live value => %d   arg_num => %d\n", value, num);
}

/*
**	Enregistre le num du registre dans la structure t_op (1 octet)
*/

static void	get_reg(t_vm *vm, t_pcb *proc, int i)
{
	proc->pc++;
	proc->op->ocp[i] = (int)vm->ram[proc->pc % MEM_SIZE].mem;
}

/*
**	Enregistre la valeur de l'index dans la structure t_op (2 octets)
*/

static void	get_ind(t_vm *vm, t_pcb *proc, int i)
{
	proc->ocp[i] = (int)vm->ram[(proc->pc + 1) % MEM_SIZE].mem;
	proc->ocp[i] += (int)(vm->ram[proc->pc % MEM_SIZE].mem * 256);
	proc->pc += 2;

/*	value = 0;
	proc->pc++;
	value = value | vm->ram[proc->pc].mem;
	proc->pc++;
	value = value << 8;
	value = value | vm->ram[proc->pc].mem;
	proc->op->ocp[num] = value;
	if ((value & 0x8000) == 0x8000)
		proc->op->ocp[num] = (value - USHRT_MAX) - 1;
		*/
}

/*
**	Prend les parametres selon l'OCP (lui applique un mask pour retenir
**	chaque pair de bits correspondant aux params, voir s'il s'agit de direct |
**	index | registre)
*/

static void	get_params(t_vm *vm, t_pcb *proc, unsigned char ocp, int i)
{
	unsigned char	param;
	unsigned char	mask;

//	ft_printf("%02x\n", vm->ram[(proc->pc + 1) % MEM_SIZE].mem);
//	ft_printf("ocp : %{RED}08b soit %02x\n", ocp, type);
	mask = 0xC0;
	mask = mask >> (2 * i);
	param = ocp & mask;
	param = param >> (6 - (2 * i));
	ft_printf("param %d : %{RED}02b\n", i, param);
	if (proc->op->code == 1)
		printf("LIVE OP CODE\n");
	if (param == REG_CODE)
		get_reg(vm, proc, i);
	if (param == DIR_CODE)
		get_dir(vm, proc, i);
	if (param == IND_CODE)
		get_ind(vm, proc, i);
}

/*
**	Charge l'op du processus courant, prend les valeurs des parametres
**	selon l'OCP s'il y en un, et avance le pc
*/

void	load_op(t_vm *vm, t_pcb *proc)
{
	int i;
	t_op *op;
	unsigned char ocp;

	i = -1;
//	ft_printf("le pc est sur %#02x avec value pc : %d\n", vm->ram[proc->pc % MEM_SIZE].mem, proc->pc % MEM_SIZE);
//	ft_printf("voyons l'op, has_ocp : %d, apres %b\n", proc->op->has_ocp, (unsigned char)(&proc->op->has_ocp + 1));
	if (proc->op->has_ocp)
	{
		proc->pc++;
		ocp = vm->ram[(proc->pc) % MEM_SIZE].mem;
		while (++i < proc->op->nb_arg)
			get_params(vm, proc, ocp, i);
		op = proc->op;
//		ft_printf("inst : %s, nb arg : %d, code : %d, has ocp : %d, nb_byte : %d\nresult : ocp0 : %x, ocp1 : %x, ocp2 : %x\n", op->inst, op->nb_arg, op->code, op->has_ocp, op->nb_byte, op->ocp[0], op->ocp[1], op->ocp[2]);
	}
	else
	{
		get_dir(vm, proc, 0);
	}
	proc->pc++;
}
