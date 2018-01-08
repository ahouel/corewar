/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:54:43 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/02 14:56:25 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	On vérifie si la ligne passée contient bien le commentaire. Si oui, on le
**	récupère. 
**	!!! manque la gestion d'erreur sur la fin de la ligne, après le commentaire
*/

static void	check_comment(char **input, header_t *head, t_champ *pl, int i)
{
	int		j;
	int		k;

	if (ft_strncmp(input[i], ".comment", 8) != 0)
		return ;
	if ((head->comment)[0] != 0)
		exit_free("a champ can have only one comment\n", pl, input);
	j = 8;
	while (ft_iswhitespace(input[i][j]))
		j++;
	k = 0;
	while (input[i][++j] && input[i][j] != '\"' && k < COMMENT_LENGTH)
		(head->comment)[k++] = input[i][j];
}

/*
** Meme remarque que pour check_comment mais concernant le nom du champion.
*/

static void	check_name(char **input, header_t *head, t_champ *pl, int i)
{
	int		j;
	int		k;

	if (ft_strncmp(input[i], ".name", 5) != 0)
		return ;
	if ((head->prog_name)[0] != 0)
		exit_free("a champ can have only one name\n", pl, input);
	j = 5;
	while (ft_iswhitespace(input[i][j]))
		j++;
	k = 0;
	while (input[i][++j] && input[i][j] != '\"' && k < PROG_NAME_LENGTH)
		(head->prog_name)[k++] =input[i][j];
}

/*
**	On parcourt les lignes du .s en sautant celles de commentaires.
**	!!! à rendre plus propre quand les deux fonctions au dessus seront rénovées
*/

t_champ		*manage_header(char **input, t_champ *pl)
{
	int			i;
	header_t	*head;

	i = 0;
	if (!(head = ft_memalloc(sizeof(header_t))))
		exit_free("unsuccessful malloc\n", pl, input);
	while (input[i][0] == COMMENT_CHAR)
		i++;
	check_name(input, head, pl, i);
	if ((head->prog_name)[0] == 0)
		exit_free("has to be a name on the top of a file\n", pl, input);
	while (input[++i][0] == COMMENT_CHAR)
		;
	check_comment(input, head, pl, i);
	if ((head->comment)[0] == 0)
		exit_free("has to be a comment right under the name\n", pl, input);
	i++;
	pl->head = head;
	return (do_parsing(pl, input, i));
}
