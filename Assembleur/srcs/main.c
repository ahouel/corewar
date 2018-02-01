/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:56:27 by lgaveria          #+#    #+#             */
/*   Updated: 2018/02/01 14:29:27 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	On ouvre et lit le fichier rentré en paramètre. Il est renvoyé sous forme de
**	tableau qui est réalloué à chaque appelle de gnl.
*/

static char		**read_champ(char *file_name)
{
	char	**ret;
	int		fd;
	int		i;
	int		gnl_ret;

	if (ft_strncmp(&(file_name[ft_strlen(file_name) - 2]), ".s", 2) != 0)
		exit_free("extension's file must be [.s]", NULL, NULL, 0);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit_free("invalid file\n", NULL, NULL, 0);
	if (!(ret = malloc(sizeof(char*) * 1)))
		exit_free("unsuccessful malloc\n", NULL, NULL, 0);
	i = 0;
	while ((gnl_ret = get_next_line(fd, &(ret[i]))) > 0)
	{
		if (!(ret = realloc(ret, sizeof(char*) * (i + 2))))
			exit_free("unsuccessful malloc\n", NULL, NULL, 0);
		ret[++i] = NULL;
	}
	if (gnl_ret == -1)
		exit_free("unsuccessful read\n", NULL, NULL, 0);
	close(fd);
	return (ret);
}

/*
** Simplifie le parsing en supprimant les commentaires en fin de ligne.
*/

static char		**cut_comment(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] && tab[i][j] != COMMENT_CHAR && tab[i][j] != COM_CHAR)
			j++;
		if (tab[i][j])
		{
			while (j >= 0 && ft_iswhitespace(tab[i][j]))
				j--;
			tmp = tab[i];
			if (j < 0)
				tab[i] = ft_strdup("#");
			else
				tab[i] = ft_strsub(tab[i], 0, j);
			free(tmp);
		}
		i++;
	}
	return (tab);
}

/*
**	On boucle pour traiter un par un tous les fichiers envoyés : on le lit, on
**	récupère les informations du header et on renvoit directement tout ça dans
**	le parsing, qui renverra la structure avec tout ce qui est nécessaire
**	d'écrire dans le .cor.
*/

int				main(int argc, char **argv)
{
	int		i;
	char	**input;
	t_champ	*pl;

	i = 1;
	if (argc < 2)
		exit_free("usage : ./asm [champ to compile]\n", NULL, NULL, 0);
	while (i != argc)
	{
		if (ft_strlen(argv[i]) < 3)
			exit_free("invalid name_file\n", NULL, NULL, 0);
		input = read_champ(argv[i]);
		input = cut_comment(input);
		if (!input || ft_tablen(input) < 3)
			exit_free("invalid file\n", NULL, NULL, 0);
		if (!(pl = ft_memalloc(sizeof(t_champ))))
			exit_free("unsuccessful malloc\n", NULL, NULL, 0);
		pl->input = input;
		pl = manage_header(pl);
		end_it(pl, argv[i]);
		i++;
	}
	return (0);
}
