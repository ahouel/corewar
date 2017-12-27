/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:54:43 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/18 19:37:53 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
** on remplit tranquillement les variables qui correspondent au header dans la 
** structure
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

t_champ		*manage_header(char **input, t_champ *pl)
{
	int			i;
	header_t	*head;

	i = 0;
	if (!(head = ft_memalloc(sizeof(header_t))))
		exit_free("unsuccessful malloc\n", pl, input);
	while (input[i] && ((head->prog_name)[0] == 0 || (head->comment)[0] == 0))
	{
		if (input[i][0] == COMMENT_CHAR)
			i++;
		else
		{
			check_name(input, head, pl, i);
			check_comment(input, head, pl, i);
			i++;
		}
	}
	pl->head = head;
	return (do_parsing(pl, input, i));
}
