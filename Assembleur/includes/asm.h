/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:01:26 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/28 06:35:50 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <stdlib.h>
# include <stdio.h> //
# include "op.h"
# include "../../libft/includes/libft.h"

typedef struct	s_op
{
	char	*name;
	int		nb_param;
	int		p_type[3];
	char	*params[3];
	int		psize[3];
	char	opcode;
	int		d_siz;
	int		ocp;
	int		size;
	int		adrr_rest; //pas sure d'en avoir besoin
}				t_op;

typedef struct	s_inst
{
	int				pc;
	char			*lab_name[3];
	t_op			*op;
	int				line;
	struct s_inst	*next;
}				t_inst;

typedef struct	s_lab
{
	int				pc;
	char			*name;
	t_inst			*lst;
	struct s_lab	*next;
}				t_lab;

typedef struct	s_champ
{
	int			current_pc;
	char		**input;
	header_t	*head;
	t_lab		*lab;
}				t_champ;

/*
**	fonctions de parcours
*/

t_champ			*manage_header(t_champ *pl);
t_champ			*do_parsing(t_champ *champ, int i);
int				par_type(char *s, t_inst *cur, int p);
t_champ			*fill_label_params(t_champ *pl);
void			end_it(t_champ *champ, char *file_name);

/*
**	fonctions outil
*/

t_inst			*new_instruction(t_champ *champ, int i, int line);
t_champ			*new_label(char *name, t_champ *champ);
int				how_many_label_char(char *s);
char			*itohex(long n, int size);
int				is_direct(char *s, t_inst *cur, int param);
char			get_ocp(t_op *current);

/*
**	gestion d'erreur && free
*/

void			exit_free(char *str, t_champ *pl, int line);
void			free_tab(char **tab);
void			free_champ(t_champ *champ);
void			free_labs(t_lab *lab);
void			free_instructions(t_inst *lst);
void			free_op(t_op *op);

/*
**	fonctions a supprimer dans la version finale
*/

void			print_tab(char **tab);
void			print_lst(t_champ *champ);

/*
**	op_tab de reference
*/

extern t_op		op_tab[];

#endif
