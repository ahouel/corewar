/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_it.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:00:49 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/28 03:59:06 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	Ecriture de la structure du header dans le .cor.
**	!!! manque toujours le prog_size
*/

static void	write_header(int fd, t_champ *pl)
{
	unsigned int	tmp;

	tmp = COREWAR_EXEC_MAGIC;
	ft_bswap(&tmp, 4);
	pl->head->magic = tmp;
	tmp = pl->current_pc;
	ft_bswap(&tmp, 4);
	pl->head->prog_size = tmp;
	write(fd, pl->head, sizeof(header_t));
}

/*
**	Création ou ouverture du fichier .cor, renvoie le file descriptor
**	correspondant.
*/

static int	create_cor_file(char *file_name, t_champ *pl)
{
	char	*tmp;
	int		size;
	int		fd;

	size = ft_strlen(file_name);
	if (!(tmp = ft_memalloc(sizeof(char) * (size + 3))))
		exit_free("unsuccessful malloc\n", pl);
	tmp = ft_strncpy(tmp, file_name, size - 1);
	tmp[size - 1] = '\0';
	tmp = ft_strcat(tmp, "cor\0");
	fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(tmp);
	if (fd == -1)
		exit_free("open function failed\n", pl);
	write_header(fd, pl);
	return (fd);
}

/*
**	Ecrit dans le .cor octet par octet, en commencant par l'opcode, puis l'ocp
**	et enfin les parametres un par un.
*/

static void	write_instruction(t_op *op, int fd)
{
	int		i;
	char	tmp;
//	int		k;//
//	char	*s;

	write(fd, &(op->opcode), 1);
	if (op->ocp)
	{
		tmp = get_ocp(op);
		write(fd, &tmp, 1);
	}
	i = 0;
	while (i < op->nb_param)
	{
		/*printf("||| I = %d | SIZE = %d |||\n", i, (op->psize)[i]);
		write(1, "B\n", 2);
		if (!(s = malloc(sizeof(char) * op->psize[i])))
			return;
		write(1, "C\n", 2);
		if (!(s = ft_memcpy(s, (op->params)[i], 2)))
			return;
		write(1, "D\n", 2);
		k = 0;//
		printf("\t\t\t\t-> "); 
		while (k < op->psize[i])
		{
			printf("*");
			printf("%c", ((op->params)[i])[k] + 48);
			printf("^");
			k++;
		}
		printf("\n");*/
		write(fd, (op->params)[i], (op->psize)[i]);
//		free(s);
		i++;
	}
}

/*
**	Ecriture du header puis des instructions encodées dans le fichier. D'abord
**	l'opcode, puis l'ocp et enfin les parametres un par un.
*/

void		end_it(t_champ *pl, char *file_name)
{
	int		fd;
	t_lab	*lab;
	t_inst	*inst;

	fd = create_cor_file(file_name, pl);
	lab = pl->lab;
	while (lab)
	{
		inst = lab->lst;
		while(inst)
		{
			write_instruction(inst->op, fd);
			inst = inst->next;
		}
		lab = lab->next;
	}
	close(fd);
	write(1, file_name, ft_strlen(file_name));
	write(1, " executed\n", 10);
	free_champ(pl);
}
