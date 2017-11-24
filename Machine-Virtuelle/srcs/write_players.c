/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:24:31 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/24 13:08:47 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Recuperation du nom et du comment du champ grace au header
*/

static void				get_infos(t_player *player, header_t *hd)
{
	if (!(player->name = ft_strdup(hd->prog_name)))
		error("malloc error\n");
	if (!(player->comment = ft_strdup(hd->comment)))
		error("malloc error\n");
}


/*
**	Recuperation du champion dans son .cor.
*/

static unsigned char	*get_data(char *filename, header_t *hd)
{
	int				fd;
	char			buff[CHAMP_MAX_SIZE + SRC_BEGIN + 1];
	unsigned char	*data;
	int				ret;

	fd = 0;
	ret = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
		error("error : file\n");
	ft_bzero(buff, CHAMP_MAX_SIZE + SRC_BEGIN + 1);
	ret = read(fd, hd, sizeof(header_t));
	ft_bswap((void*)&hd->prog_size, sizeof(int));
	ft_bswap((void*)&hd->magic, sizeof(int));
	ret = read(fd, buff, hd->prog_size);
	if (!(data = (unsigned char*)ft_strnew(ret)))
		error("malloc failed\n");
	ft_memcpy(data, buff, ret);
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
	header_t		hd;

	ft_bzero(&hd, sizeof(header_t));
	i = (MEM_SIZE / vm->nb_player) * (num - 1);
	data = get_data(vm->player[nb].file_name, &hd);
	tmp = data;
	get_infos(&vm->player[nb], &hd);
	ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
			num, hd.prog_size, hd.prog_name, hd.comment);
	hd.prog_size += i;
	while (i < hd.prog_size)
	{
		vm->ram[i % MEM_SIZE].mem = *data;
		vm->ram[i % MEM_SIZE].num = nb;
		++data;
		++i;
	}
	tmp ? free(tmp) : 0;
}
