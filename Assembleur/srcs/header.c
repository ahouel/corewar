/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:54:43 by lgaveria          #+#    #+#             */
/*   Updated: 2018/02/01 15:49:34 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	check_comment(char *s, t_header *head, t_champ *pl, int count)
{
	int		i;
	char	*tmp;

	if (!(tmp = ft_strfulltrim(s)))
		exit_free("unsuccessful malloc\n", pl, NULL, 0);
	if (ft_strncmp(tmp, COMMENT_CMD_STR, ft_strlen(COMMENT_CMD_STR)) != 0)
	{
		free(tmp);
		exit_free("no comment under the name\n", pl, NULL, 0);
	}
	i = ft_strlen(COMMENT_CMD_STR);
	while (ft_iswhitespace(tmp[i]))
		i++;
	while (tmp[++i] && tmp[i] != '\"' && count < COMMENT_LENGTH)
		(head->comment)[count++] = tmp[i];
	while (tmp[++i] && ft_iswhitespace(tmp[i]))
		;
	if (tmp[i])
	{
		free(tmp);
		exit_free("wrong comment format\n", pl, NULL, 0);
	}
	free(tmp);
	return (1);
}

static void	check_name(char *s, t_header *head, t_champ *pl, int count)
{
	int		i;
	char	*tmp;

	if (!(tmp = ft_strfulltrim(s)))
		exit_free("unsuccessful malloc\n", pl, NULL, 0);
	if (tmp && ft_strncmp(tmp, NAME_CMD_STR, ft_strlen(NAME_CMD_STR)) != 0)
	{
		free(tmp);
		exit_free("no name at the top of the file\n", pl, NULL, 0);
	}
	i = ft_strlen(NAME_CMD_STR);
	while (tmp[i] && ft_iswhitespace(tmp[i]))
		i++;
	while (tmp[++i] && tmp[i] != '\"' && count < PROG_NAME_LENGTH)
		(head->prog_name)[count++] = tmp[i];
	i++;
	while (tmp[i] && ft_iswhitespace(tmp[i]))
		i++;
	if (tmp[i])
	{
		free(tmp);
		exit_free("wrong name format\n", pl, NULL, 0);
	}
	free(tmp);
}

/*
**	On recupere, en verifiant bien les potentielles erreurs de parsing, le
**	'.name' et le '.comment' du champion.
**	Les lignes de commentaires sont ignorees.
*/

t_champ		*manage_header(t_champ *pl)
{
	int			i;
	t_header	*head;
	int			com_ret;

	i = 0;
	if (!(head = ft_memalloc(sizeof(t_header))))
		exit_free("unsuccessful malloc\n", pl, NULL, 0);
	pl->head = head;
	while (pl->input[i] && ((pl->input)[i][0] == COMMENT_CHAR ||
			(pl->input)[i][0] == COM_CHAR || ft_strlen((pl->input)[i]) == 0))
		i++;
	if (pl->input[i])
		check_name((pl->input)[i], head, pl, 0);
	else
		exit_free("invalid file\n", pl, NULL, 0);
	if ((head->prog_name)[0] == 0)
		exit_free("no name at the top of a file\n", pl, NULL, 0);
	while (pl->input[++i] && ((pl->input)[i][0] == COMMENT_CHAR ||
			(pl->input)[i][0] == COM_CHAR || ft_strlen((pl->input)[i]) == 0))
		;
	if (pl->input[i])
		com_ret = check_comment((pl->input)[i], head, pl, 0);
	if (!(pl->input[i]) || !com_ret)
		exit_free("no comment under the name\n", pl, NULL, 0);
	return (do_parsing(pl, i));
}
