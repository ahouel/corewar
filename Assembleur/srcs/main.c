/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:56:27 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/02 15:02:03 by lgaveria         ###   ########.fr       */
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
		exit_free("extension's file must be [.s]", NULL, NULL);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit_free("invalid file\n", NULL, NULL);
	if (!(ret = malloc(sizeof(char*) * 1)))
		exit_free("unsuccessful malloc\n", NULL, NULL);
	i = 0;
	while ((gnl_ret = get_next_line(fd, &(ret[i]))) > 0)
	{
		if (!(ret = realloc(ret, sizeof(char*) * (i + 2))))
			exit_free("unsuccessful malloc\n", NULL, NULL);
		ret[++i] = NULL;
	}
	if (gnl_ret == -1)
		exit_free("unsuccessful read\n", NULL, ret); //erreur a gerer
	close(fd);
	return (ret);
}

/*
**	On boucle pour traiter un par un tous les fichiers envoyés : on le lit, on
**	récupère les informations du header et on renvoit directement tout ça dans
**	le parsing, qui renverrat la structure avec tout ce qui est nécessaire
**	d'écrire dans le .cor.
*/

int				main(int argc, char **argv)
{
	int		i;
	char	**input;
	t_champ	*pl;

	i = 1;
	if (argc < 2)
		exit_free("usage : ./asm [champ to compile]\n", NULL, NULL);
	while (i != argc)
	{
		input = read_champ(argv[i]);
		if (!input)
			exit_free("invalid file\n", NULL, NULL);
		if (!(pl = ft_memalloc(sizeof(t_champ))))
			exit_free("unsuccessful malloc\n", NULL, input);
		pl = manage_header(input, pl);
		free_tab(input); // sera modifie
		print_lst(pl); //
		end_it(pl, argv[i]);
		i++;
	}
	return (0);
}
