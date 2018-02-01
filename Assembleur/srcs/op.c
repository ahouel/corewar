/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/02/01 11:35:01 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_D}, {NULL}, {0}, 1, 4, 0, 1},
	{"ld", 2, {T_D | T_I, T_REG},
		{NULL}, {0}, 2, 4, 1, 1},
	{"st", 2, {T_REG, T_I | T_REG}, {NULL}, {0}, 3, 0, 1, 1},
	{"add", 3, {T_REG, T_REG, T_REG}, {NULL}, {0}, 4, 0, 1, 1},
	{"sub", 3, {T_REG, T_REG, T_REG}, {NULL}, {0}, 5, 0, 1, 1},
	{"and", 3, {T_REG | T_D | T_I, T_REG | T_I | T_D, T_REG},
		{NULL}, {0}, 6, 4, 1, 1},
	{"or", 3, {T_REG | T_I | T_D, T_REG | T_I | T_D, T_REG},
		{NULL}, {0}, 7, 4, 1, 1},
	{"xor", 3, {T_REG | T_I | T_D, T_REG | T_I | T_D, T_REG},
		{NULL}, {0}, 8, 4, 1, 1},
	{"zjmp", 1, {T_D}, {NULL}, {0}, 9, 2, 0, 1},
	{"ldi", 3, {T_REG | T_D | T_I, T_D | T_REG, T_REG},
		{NULL}, {0}, 10, 2, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_D | T_I, T_D | T_REG},
		{NULL}, {0}, 11, 2, 1, 1},
	{"fork", 1, {T_D}, {NULL}, {0}, 12, 2, 0, 1},
	{"lld", 2, {T_D | T_I, T_REG}, {NULL}, {0},
		13, 4, 1, 1},
	{"lldi", 3, {T_REG | T_D | T_I, T_D | T_REG, T_REG},
		{NULL}, {0}, 14, 2, 1, 1},
	{"lfork", 1, {T_D}, {NULL}, {0}, 15, 2, 0, 1},
	{"aff", 1, {T_REG}, {NULL}, {0}, 16, 0, 1, 1},
	{NULL, 0, {0}, {NULL}, {0}, 0, 0, 0, 0}
};
