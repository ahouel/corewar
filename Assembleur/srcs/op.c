/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/01/16 18:55:23 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_op	op_tab[17] =
{
	{"live", 1, {T_DIR}, {NULL}, 1, 0, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, {NULL}, 2, 1, 0, 1},
	{"st", 2, {T_REG, T_IND | T_REG}, {NULL}, 3, 1, 0, 1},
	{"add", 3, {T_REG, T_REG, T_REG}, {NULL}, 4, 1, 0, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, {NULL}, 5, 1, 0, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		{NULL}, 6, 1, 0, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		{NULL}, 7, 1, 0, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		{NULL}, 8, 1, 0, 1},
	{"zjmp", 1, {T_DIR}, {NULL}, 9, 0, 1, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		{NULL}, 10, 1, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		{NULL}, 11, 1, 1, 1},
	{"fork", 1, {T_DIR}, {NULL}, 12, 0, 1, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, {NULL}, 13, 1, 0, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		{NULL}, 14, 1, 1, 0},
	{"lfork", 1, {T_DIR}, {NULL}, 15, 0, 1, 0},
	{"aff", 1, {T_REG}, {NULL}, 16, 1, 0, 0},
	{NULL, 0, {0}, {NULL}, 0, 0, 0, 0}
};
