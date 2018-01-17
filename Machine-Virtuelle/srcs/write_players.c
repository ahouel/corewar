/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:24:31 by ahouel            #+#    #+#             */
/*   Updated: 2018/01/17 16:07:48 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Regarde si la taille du champion correspond a celle du header
*/

static void				is_player_valid(t_vm *vm,
		t_header *hd, char *filename, int ret)
{
	if (ret != hd->prog_size)
	{
		ft_printf("%{RED}s %{BLUE}s\n",
				"Error : wrong program size in the file", filename);
		error(vm, "");
	}
}

/*
**	regarde si les valeurs du header sont valides
*/

static void				is_header_valid(t_vm *vm, char *filename, t_header *hd)
{
	if (hd->magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf("%{RED}s %{BLUE}s\n", "Error : wrong magic number for file",
				filename);
		error(vm, "");
	}
	if (hd->prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf("%{RED}s %{BLUE}s\n",
				"Error : program size too big (over CHAMP_MAX_SIZE) for file",
				filename);
		error(vm, "");
	}
}

/*
**	Recuperation du nom et du comment du champ grace au header
*/

static void				get_infos(t_vm *vm, t_player *player, t_header *hd)
{
	if (!(player->name = ft_strdup(hd->prog_name)))
		error(vm, "malloc failed");
	if (!(player->comment = ft_strdup(hd->comment)))
		error(vm, "malloc failed");
}

/*
**	Recuperation du champion dans son .cor.
*/

static unsigned char	*get_data(t_vm *vm, char *filename, t_header *hd)
{
	int				fd;
	char			buff[CHAMP_MAX_SIZE + 2];
	unsigned char	*data;
	int				ret;

	fd = 0;
	ret = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("%{RED}s %{BLUE}s\n", "Error : can't open file", filename);
		error(vm, "");
	}
	ft_bzero(buff, CHAMP_MAX_SIZE + 2);
	ret = read(fd, hd, sizeof(t_header));
	ft_bswap((void*)&hd->prog_size, sizeof(int));
	ft_bswap((void*)&hd->magic, sizeof(int));
	is_header_valid(vm, filename, hd);
	ret = read(fd, buff, hd->prog_size + 1);
	is_player_valid(vm, hd, filename, ret);
	if (!(data = (unsigned char*)ft_strnew(ret)))
		error(vm, "malloc failed");
	ft_memcpy(data, buff, ret);
	close(fd);
	return (data);
}

/*
**	Ecriture des joueurs sur la ram. /!\ TO DO : check errors sur le header.
*/

void					write_players(t_vm *vm, int nb, int num)
{
	int				i;
	unsigned char	*data;
	unsigned char	*tmp;
	t_header		hd;

	ft_bzero(&hd, sizeof(t_header));
	i = (MEM_SIZE / vm->nb_player) * (num - 1);
	data = get_data(vm, vm->player[nb].file_name, &hd);
	tmp = data;
	get_infos(vm, &vm->player[nb], &hd);
	ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
			nb + 1, hd.prog_size, hd.prog_name, hd.comment);
	hd.prog_size += i;
	while (i < hd.prog_size)
	{
		vm->ram[i % MEM_SIZE].mem = *data;
		vm->ram[i % MEM_SIZE].num = nb + 1;
		++data;
		++i;
	}
	tmp ? free(tmp) : 0;
}
