/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:22:35 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/03 17:44:45 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Enregistre la valeur direct dans la structure t_op
**	Recup : 2 Octets si le nb_byte est de 0,
**	4 Octets autrement
*/

static void	get_dir(t_vm *vm, t_pcb *proc, int i)
{
	int	value;

	value = (int)vm->ram[proc->pc % MEM_SIZE].mem;
	value <<= 8;
	value |= (int)vm->ram[(proc->pc + 1) % MEM_SIZE].mem;
	if (!proc->op->nb_byte)
	{
		value <<= 8;
		value |= (int)vm->ram[(proc->pc + 2) % MEM_SIZE].mem;
		value <<= 8;
		value |= (int)vm->ram[(proc->pc + 3) % MEM_SIZE].mem;
		proc->op->param[i] = value;
	}
	else
		proc->op->param[i] = (signed short)value;
	proc->op->nb_byte ? (proc->pc += 2) : (proc->pc += 4);
}

/*
**	Enregistre le num du registre dans la structure t_op (1 octet)
*/

static void	get_reg(t_vm *vm, t_pcb *proc, int i)
{
	proc->op->param[i] = (int)vm->ram[proc->pc % MEM_SIZE].mem;
	proc->pc++;
}

/*
**	Enregistre la valeur trouvee a l'index (addresse 2 octet)
**	dans la structure t_op (4 octets)
*/

static void	get_ind(t_vm *vm, t_pcb *proc, int i)
{
	int	addr;

	addr = (int)vm->ram[proc->pc % MEM_SIZE].mem;
	addr <<= 8;
	addr |= (int)vm->ram[(proc->pc + 1) % MEM_SIZE].mem;
	proc->op->param[i] = (signed short)addr;
	proc->pc += 2;
}

/*
**	Prend les parametres selon l'OCP (lui applique un mask pour retenir
**	chaque pair de bits correspondant aux params, voir s'il s'agit de direct |
**	index | registre)
**	Enregistre le type de param dans la struct op (param_type)
*/

static void	get_params(t_vm *vm, t_pcb *proc, unsigned char ocp, int i)
{
	unsigned char	param;
	unsigned char	mask;

	mask = 0xC0;
	mask = mask >> (2 * i);
	param = ocp & mask;
	param = param >> (6 - (2 * i));
	proc->op->param_type[i] = param;
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

void		load_op(t_vm *vm, t_pcb *proc)
{
	unsigned char	ocp;
	int				i;

	i = -1;
	ocp = 0x80;
	if (proc->op->has_ocp)
	{
		proc->pc++;
		ocp = vm->ram[(proc->pc) % MEM_SIZE].mem;
		if (!ocp_is_valid(vm, proc, ocp))
			return ;
	}
	proc->pc++;
	while (++i < proc->op->nb_arg)
		get_params(vm, proc, ocp, i);
}
