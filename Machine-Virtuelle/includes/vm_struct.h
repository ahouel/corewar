/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:08:08 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/24 11:54:18 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// VM = https://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C

#ifndef VM_STRUCT_H
# define VM_STRUCT_H

#define INST_IDLE 0
#define INST_NAME 1
#define INST_OCP 2
#define INST_ARG 2

#define	IDLE 	1
#define	WAIT 	2
#define	READY 	3
#define START 	4
#define DEAD	5

#define RUN 1

#define	MAGIC_NB 4
#define PROG_NAME 128 + 4
#define PROG_COMS 2048 + 4
#define	PROG_SIZE 4

#define D4 0
#define D2 1

#define SRC_BEGIN MAGIC_NB + PROG_NAME + PROG_COMS + PROG_SIZE

#define BLING_DELAY 65
#define BLING_LIVE 45
#define NCURSES_DELAY 100000

typedef struct s_vm		t_vm;
typedef struct s_pcb	t_pcb;

/*
**	Structure des operation (labels)
*/

typedef struct s_op
{
	char	*inst;
	void	(*func)(t_vm *vm, t_pcb *proc);
	int		nb_arg;
	int		ocp[3];
	int		code;
	int		loadtime;
	char	*name;
	int		has_ocp;
	int		nb_byte;
}				t_op;

/*
**	Joueur (.cor)
*/

typedef struct s_player
{
	char	*name;
	char	*comment;
	int		active;
	int		life_signal;
	int		last_live;
	char	*file_name;
}	t_player;

/*
**	https://openclassrooms.com/courses/la-programmation-systeme-en-c-sous-unix/les-processus-1
**	Processus
*/

typedef struct s_pcb
{
	int		pid;	//process identifier
	int		uid;	//user idetifier
	int		last_pc;
	int		pc;// L adresse dans la ram du processus
	char	state;
	char	carry;
	int		reg[REG_NUMBER + 1];
	int		last_live; // si le processus a fait appel a live durant CYCLE_TO_DIE
	t_op	*op;
	struct	s_pcb	*next;
}	t_pcb;

/*
**	Representation de la memoire (ram)
*/

typedef struct s_mem
{
	unsigned char	mem;
	int				num;
	int				flash;
}	t_mem;
/*
typedef struct s_optab
{
	char	*inst;
	void	(*func)(t_vm *vm, t_pcb *proc);
	int		nb_arg;
	int		ocp[3];
	int		code;
	int		loadtime;
	char	*name;
	int		need_ocp;
	int		direct_size; 	// nombre d'octect d'encodage. 2 ou 4;
}	t_optab;
*/

extern t_op op_tab[];

/*
**	Environnement de la vm
*/

typedef struct s_vm
{
	int		nb_player;		//nombre de joueur
	int		ctd;			//cycle_to_die
	int		cycle;			//cycle en cours
	char	pause;			// pause 0 / unpause 1
	char	ncurses;		// oui : 1 / non : 1
	int		delay;			// delay pour ncurse
	int		next_ctd;		// prochain cycle to die
	int		ctd_check;
	int		dump;			// -d
	int		debug;
	int		verbosity;		// -v
//	int		lives_in_cycle;	// define
	t_mem	ram[MEM_SIZE];
//	int		life_signal[4];			// tab pour les vies.
//	char	*files_name[5];
	t_player	player[MAX_PLAYERS];
	t_player	*last_one;

	//void	(*op_tab[20])(struct s_vm *vm, t_op *op, int player);

	t_pcb	*proc;
}	t_vm;

#endif
