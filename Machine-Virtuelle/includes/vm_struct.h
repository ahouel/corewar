/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:08:08 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/18 17:16:16 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_STRUCT_H
# define VM_STRUCT_H

/*
**	Header de chaque files.cor
*/

typedef struct			s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}						t_header;

/*
**	Joueur (.cor)
*/

typedef struct			s_player
{
	char	*file_name;
	char	*name;
	char	*comment;
	int		active;
	int		lives_count;
	int		last_live;
	int		id_color;
}						t_player;

/*
**	https://openclassrooms.com/courses/la-programmation-systeme-en-c-sous-unix/
**	les-processus-1
**	Processus
*/

typedef struct			s_pcb
{
	char			carry;
	char			aff;
	int				pid;
	int				uid;
	int				pc;
	int				last_live;
	struct s_op		*op;
	int				reg[REG_NUMBER];
	struct s_pcb	*next;
}						t_pcb;

/*
**	Representation de la memoire (ram)
*/

typedef struct			s_mem
{
	unsigned char	mem;
	char			live;
	char			store;
	int				num;
}						t_mem;

/*
**	aff du ncurses
*/

typedef struct			s_aff
{
	int				in[MAX_PLAYERS];
	int				end[MAX_PLAYERS];
}						t_aff;

/*
**	Environnement de la vm
*/

typedef struct			s_vm
{
	char		ncurses;
	char		pause;
	char		aff;
	int			nb_player;
	int			cycle;
	int			delay;
	int			ctd;
	int			next_ctd;
	int			last_ctd_decay;
	int			period_lives;
	int			dump;
	int			verbosity;
	int			nb_proc;
	int			next_pid;
	t_pcb		*proc_lst;
	t_player	player[MAX_PLAYERS];
	t_mem		ram[MEM_SIZE];
}						t_vm;

/*
**	Structure des operation (labels)
*/

typedef struct			s_op
{
	char	*label;
	void	(*func)(struct s_vm *vm, struct s_pcb *proc);
	int		nb_arg;
	int		param_type[3];
	int		param[3];
	int		code;
	int		loadtime;
	char	*name;
	int		has_ocp;
	int		nb_byte;
	int		addr_rest;
}						t_op;

/*
**	op_tab de reference
*/

extern t_op				g_op_tab[];

#endif
