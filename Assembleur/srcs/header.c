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

static void	check_comment(char *s, header_t *head, t_champ *pl)
{
	int		i;
	int		count;

	if (ft_strncmp(s, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) != 0)
		exit_free("no comment under the name\n", pl);
	if ((head->comment)[0] != 0)
		exit_free("a champ can have only one comment\n", pl);
	i = ft_strlen(COMMENT_CMD_STRING);
	while (ft_iswhitespace(s[i]))
		i++;
	count = 0;
	while (s[++i] && s[i] != '\"' && count < COMMENT_LENGTH)
		(head->comment)[count++] = s[i];
	i++;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i] && s[i] != '#')
		exit_free("format comment line\n", pl);
}

static void	check_name(char *s, header_t *head, t_champ *pl)
{
	int		i;
	int		count;

	if (ft_strncmp(s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) != 0)
		exit_free("no name at the top of the file\n", pl);
	if ((head->prog_name)[0] != 0)
		exit_free("a champ can have only one name\n", pl);
	i = ft_strlen(NAME_CMD_STRING);
	while (ft_iswhitespace(s[i]))
		i++;
	count = 0;
	i++;
	while (s[i] && s[i] != '\"' && count < PROG_NAME_LENGTH)
		(head->prog_name)[count++] = s[i++];
	i++;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i] && s[i] != '#')
		exit_free("format name line\n", pl);
}

/*
**	On recupere, en verifiant bien les potentielles erreurs de parsing, le
**	'.name' et le '.comment' du champion.
**	Les lignes de commentaires sont ignorees.
*/

t_champ		*manage_header(t_champ *pl)
{
	int			i;
	header_t	*head;

	i = 0;
	if (!(head = ft_memalloc(sizeof(header_t))))
		exit_free("unsuccessful malloc\n", pl);
	pl->head = head;
	while ((pl->input)[i][0] == COMMENT_CHAR)
		i++;
	check_name((pl->input)[i], head, pl);
	if ((head->prog_name)[0] == 0)
		exit_free("no name at the top of a file\n", pl);
	i++;
	while ((pl->input)[i][0] == COMMENT_CHAR)
		i++;
	check_comment((pl->input)[i], head, pl);
	if ((head->comment)[0] == 0)
		exit_free("no comment under the name\n", pl);
	i++;
	return (do_parsing(pl, i));
}
