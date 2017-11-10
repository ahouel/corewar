/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:21:58 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/10 15:43:06 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_prog_size(char *data)
{
	int ret;

	data += MAGIC_NB;
	data += PROG_NAME;
	ret = 0x0;
	ret = ret | (unsigned char)*data;
	ret = ret << 8;
	ret = ret | (unsigned char)data[1];
	ret = ret << 8;
	ret = ret | (unsigned char)data[2];
	ret = ret << 8;
	ret = ret | (unsigned char)data[3];
	return (ret);
}

static char	*get_data(char *filename)
{
	int		fd;
	char	buff[4096];
	char	*data;
	int		ret;

	fd = 0;
	ret = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("error : file\n");
	ret = read(fd, buff, 4096);
	data = ft_memalloc(ret + 1);
	ft_memcpy(data, buff, ret);
	return (data);
}

void	write_players(t_vm *vm, int nb, int num)
{
	printf("Write Player\n");
	int		i;
	char	*data;
	char	*data_tmp;
	int		prog_size;

	i = (MEM_SIZE / vm->nb_player) * num;

	// printf("File Name %s\n", vm->player[nb].file_name);
	data = get_data(vm->player[nb].file_name);

	// printf(">>>>>>$$> %s\n", data);
	prog_size = get_prog_size(data);

	// printf("prog_size => %d\n", prog_size);
	data_tmp = data + SRC_BEGIN;

	// printf("I => %d\n", i);
	prog_size += i;
	while (i < prog_size)
	{
		//vm->mem[i % MEM_SIZE] = (unsigned char)*data_tmp;
		vm->ram[i % MEM_SIZE].mem = (unsigned char)*data_tmp;
		// printf(">__&>>> %d\n", (num + 1) * -1);
		vm->ram[i % MEM_SIZE].num = (num + 1) * -1;
		data_tmp++;
		i++;
	}
	// show_mem(vm);
}
