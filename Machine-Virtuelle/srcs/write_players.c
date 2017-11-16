/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:24:31 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/16 17:18:57 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Recuperation du champion dans son .cor.
*/

static char	*get_data(char *filename, header_t *hd)
{
	int		fd;
	char	buff[CHAMP_MAX_SIZE + SRC_BEGIN + 1];
	char	*data;
	int		ret;

	fd = 0;
	ret = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
		error("error : file\n");
	ft_bzero(buff, CHAMP_MAX_SIZE + SRC_BEGIN + 1);
	ret = read(fd, hd, sizeof(header_t));
	ft_bswap((void*)&hd->prog_size, sizeof(int));
	ft_bswap((void*)&hd->magic, sizeof(int));
	ret = read(fd, buff, hd->prog_size);
	if (!(data = ft_strnew(ret)))
		error("malloc failed\n");
	ft_memcpy(data, buff, ret);
	return (data);
}

/*
**	Ecriture des joueurs sur la ram. /!\ TO DO : check errors sur le header.
*/

void		write_players(t_vm *vm, int nb, int num)
{
	int			i;
	char		*data;
	char		*data_tmp;
	header_t	hd;

	ft_bzero(&hd, sizeof(header_t));
	i = (MEM_SIZE / vm->nb_player) * num;
	data = get_data(vm->player[nb].file_name, &hd);
	data_tmp = data + SRC_BEGIN;
	ft_printf("%s\n", *data_tmp);
	ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\")\n",
			num + 1, hd.prog_size, hd.prog_name, hd.comment);
	hd.prog_size += i;
	while (i < hd.prog_size)
	{
		vm->ram[i % MEM_SIZE].mem = (unsigned char)*data_tmp;
		vm->ram[i % MEM_SIZE].num = num + 1;
		data_tmp++;
		i++;
	}
	data ? free(data) : 0;
}
