/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_it.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:00:49 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/18 19:37:46 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	create_cor_file(char *file_name, t_champ *pl)
{
	char	*tmp;
	int		size;
	int		fd;

	size = ft_strlen(file_name);
	if ((tmp = ft_strstr(file_name, ".s")))
	{
		if(!(tmp[2]))
		{
			if (!(tmp = malloc(sizeof(char) * (size + 3))))
				exit_free("unsuccessful malloc\n", pl, NULL);
			tmp = ft_strncpy(tmp, file_name, size - 1);
			tmp[size - 1] = '\0';
			tmp = ft_strcat(tmp, "cor\0");
			fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			free(tmp);
			return (fd);
		}
	}
	else
		exit_free("invalid file name\n", pl, NULL);
	return (-1);
}

static void	write_header(int fd, t_champ *pl)
{
	unsigned int	tmp;

	tmp = COREWAR_EXEC_MAGIC;
	ft_bswap(&tmp, 4);
	pl->head->magic = tmp;
	write(fd, pl->head, sizeof(header_t));
	free(pl->head);
	pl->head = NULL;
}

void		end_it(t_champ *champ, char *file_name)
{
	int fd;
	int i;
	int j;

	fd = create_cor_file(file_name, champ);
	write_header(fd, champ);
	i = 0;
	j = 0;
	while (file_name[i])
	{
		if (file_name[i] == '/')
			j = i;
		i++;
	}
	write(1, &(file_name[j + 1]), ft_strlen(file_name) - (j + 1));
	write(1, " done\n", 6);
	free_champ(champ);
}
