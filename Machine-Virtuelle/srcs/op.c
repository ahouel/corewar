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

#include "vm.h"

t_op	g_op_tab[17] =
{
	{"live", &live, 1, {T_DIR}, {0}, 1, 10, "alive", 0, 0, 0},
	{"ld", &ld, 2, {T_DIR | T_IND, T_REG}, {0}, 2, 5, "load", 1, 0, 1},
	{"st", &st, 2, {T_REG, T_IND | T_REG}, {0}, 3, 5, "store", 1, 0, 1},
	{"add", &add, 3, {T_REG, T_REG, T_REG}, {0}, 4, 10, "addition", 1, 0, 0},
	{"sub", &sub, 3, {T_REG, T_REG, T_REG}, {0}, 5, 10, "soustraction",
		1, 0, 0},
	{"and", &gates, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		{0}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3)", 1, 0, 1},
	{"or", &gates, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		{0}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3)", 1, 0, 1},
	{"xor", &gates, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		{0}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3)", 1, 0, 1},
	{"zjmp", &zjmp, 1, {T_DIR}, {0}, 9, 20, "jump if zero", 0, 1, 0},
	{"ldi", &ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		{0}, 10, 25, "load index", 1, 1, 1},
	{"sti", &sti, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		{0}, 11, 25, "store index", 1, 1, 1},
	{"fork", &ft_fork, 1, {T_DIR}, {0}, 12, 800, "fork", 0, 1, 1},
	{"lld", &ld, 2, {T_DIR | T_IND, T_REG}, {0}, 13, 10, "long load",
		1, 0, 0},
	{"lldi", &ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		{0}, 14, 50, "long load index", 1, 1, 0},
	{"lfork", &ft_fork, 1, {T_DIR}, {0}, 15, 1000, "long fork", 0, 1, 0},
	{"aff", &aff, 1, {T_REG}, {0}, 16, 2, "aff", 1, 0, 0},
	{0, 0, 0, {0}, {0}, 0, 0, 0, 0, 0, 0}
};
