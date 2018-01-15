/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:08:08 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/15 14:17:13 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_STRUCT_H
# define VM_STRUCT_H

/*
**	https://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C
*/

//#define D4 0
//#define D2 1

# define BLING_DELAY 65
# define BLING_LIVE 45
# define NCURSES_DELAY 100000

typedef struct s_vm		t_vm;
typedef struct s_pcb	t_pcb;

/*
**	Header de chaque files.cor
*/

typedef struct		header_s
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					header_t;

/*
**	Structure des operation (labels)
*/

typedef struct s_op
{
	char	*label;
	void	(*func)(t_vm *vm, t_pcb *proc);
	int		nb_arg;
	int		param_type[3];
	int		param[3];
	int		code;
	int		loadtime;
	char	*name;
	int		has_ocp;
	int		nb_byte;
	int		addr_rest;
}				t_op;

/*
**	op_tab de reference
*/

extern t_op g_op_tab[];

/*
**	Joueur (.cor)
*/

typedef struct	s_player
{
	char	*file_name;
	char	*name;
	char	*comment;
	int		active;
	int		lives_count;
	int		last_live;
	int		id_color;
}				t_player;

/*
**	https://openclassrooms.com/courses/la-programmation-systeme-en-c-sous-unix/les-processus-1
**	Processus
*/

typedef struct	s_pcb
{
	char	carry;
	int		pid;
	int		uid;
	int		pc;
	int		last_live;
	t_op	*op;
	int		reg[REG_NUMBER + 1];
	struct	s_pcb	*next;
}				t_pcb;

/*
**	Representation de la memoire (ram)
*/

typedef struct	s_mem
{
	unsigned char	mem;
	int				num;
	int				flash;
}				t_mem;

/*
**	Environnement de la vm
*/

typedef struct	s_vm
{
	char		ncurses;
	char		pause;
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
}				t_vm;

#endif
