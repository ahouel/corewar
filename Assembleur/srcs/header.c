/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:54:43 by lgaveria          #+#    #+#             */
/*   Updated: 2018/02/08 16:01:56 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	fill_comment(t_champ *pl, t_header *head, int i, int j)
{
	int		count;

	count = 0;
	while (pl->input[i] && pl->input[i][j] != '\"')
	{
		while (pl->input[i][j] && pl->input[i][j] != '\"' && count < COM_LEN)
			head->comment[count++] = pl->input[i][j++];
		if (!(pl->input[i][j]))
		{
			head->comment[count++] = '\n';
			i++;
			j = 0;
		}
		if (count >= COM_LEN)
			exit_free(COM_SIZE, pl, NULL, COM_LEN);
	}
	if (!(pl->input[i]))
		exit_free(COM_NOEND, pl, NULL, 0);
	while (pl->input[i][++j])
		if (!(ft_iswhitespace(pl->input[i][j])))
			exit_free(COM_LINE_FORM, pl, NULL, 0);
	return (i + 1);
}

static int	check_comment(t_header *head, t_champ *pl, int line)
{
	int		i;
	int		j;

	i = line;
	j = 0;
	while (pl->input[i][j] && ft_iswhitespace(pl->input[i][j]))
		j++;
	if (ft_strncmp(&(pl->input[i][j]), COMMENT_STR, ft_strlen(COMMENT_STR)))
		exit_free(NO_COM, pl, NULL, 0);
	j += ft_strlen(COMMENT_STR);
	while (pl->input[i][j] && ft_iswhitespace(pl->input[i][j]))
		j++;
	if (pl->input[i][j++] != '\"')
		exit_free(COM_FORM, pl, NULL, 0);
	i = fill_comment(pl, head, i, j);
	return (i - line);
}

static void	check_name(char *s, t_header *head, t_champ *pl, int count)
{
	int		i;
	char	*tmp;

	if (!(tmp = ft_strfulltrim(s)))
		exit_free(ERR_MALLOC, pl, NULL, 0);
	if (tmp && ft_strncmp(tmp, NAME_STR, ft_strlen(NAME_STR)) != 0)
	{
		free(tmp);
		exit_free(NO_NAME, pl, NULL, 0);
	}
	i = ft_strlen(NAME_STR);
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
		exit_free(NAME_FORM, pl, NULL, 0);
	}
	free(tmp);
}

/*
**	On recupere, en verifiant bien les potentielles erreurs de parsing, le
**	'.name' et le '.comment' du champion.
**	Les lignes de commentaires sont ignorees.
*/

t_champ		*manage_header(t_champ *pl, int i)
{
	t_header	*head;
	int			com_ret;

	com_ret = 0;
	if (!(head = ft_memalloc(sizeof(t_header))))
		exit_free(ERR_MALLOC, pl, NULL, 0);
	pl->head = head;
	while (pl->input[i] && ((pl->input)[i][0] == COMMENT_CHAR ||
			(pl->input)[i][0] == COM_CHAR || ft_strlen((pl->input)[i]) == 0))
		i++;
	if (pl->input[i])
		check_name((pl->input)[i], head, pl, 0);
	else
		exit_free("invalid file", pl, NULL, 0);
	if ((head->prog_name)[0] == 0)
		exit_free(NO_NAME, pl, NULL, 0);
	while (pl->input[++i] && ((pl->input)[i][0] == COMMENT_CHAR ||
			(pl->input)[i][0] == COM_CHAR || ft_strlen((pl->input)[i]) == 0))
		;
	if (pl->input[i])
		com_ret = check_comment(head, pl, i);
	i += com_ret;
	if (!(pl->input[i]) || !com_ret)
		exit_free(NO_COM, pl, NULL, 0);
	return (do_parsing(pl, i - 1));
}
