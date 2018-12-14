/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tube_ant.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 14:51:15 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 16:43:38 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lem_in.h"

int		check_comment(t_lem *box, char *line)
{
	if (line[1] != '#')
		return (1);
	else if (line[1] == '#')
	{
		line += 2;
		if (ft_strcmp(line, "start") == 0 && box->step == 2)
			box->rtype = 1;
		else if (ft_strcmp(line, "end") == 0 && box->step == 2)
			box->rtype = 2;
		return (1);
	}
	return (0);
}

int		get_tube_room(t_lem *box, char **split)
{
	t_room	*tmp1;
	t_room	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	find_room(box->room, split[0], &tmp1);
	find_room(box->room, split[1], &tmp2);
	if (!tmp1 || !tmp2)
		return (1);
	tmp1->nb_link++;
	tmp2->nb_link++;
	if (add_room(tmp1, &tmp2->link) && add_room(tmp2, &tmp1->link))
		return (0);
	return (1);
}

int		verif_tube(t_lem *b, char *line)
{
	char **split;

	if (*line == '#')
		return (check_comment(b, line));
	if (!ft_strchr(line, '-') || !b->room || ft_strchr(line, ' ') ||
		(ft_strchr(line, '-') != ft_strrchr(line, '-')))
		return (0);
	split = ft_strsplit(line, '-');
	if (!split[0] || !split[1] || split[2])
		return (ft_freesplit(split));
	else if (get_tube_room(b, split))
		return (ft_freesplit(split));
	ft_freesplit(split);
	return (1);
}

int		verif_ant(t_lem *box, char *line)
{
	uintmax_t	nb;

	if (*line == '#')
		return (check_comment(box, line));
	if (*line == '-')
		return (0);
	if (ft_str_is_numeric(line) && ft_check_limit(line, UINT_LIMIT))
	{
		nb = ft_atoui(line);
		if (nb > 0)
		{
			box->ant = nb;
			box->step = 2;
			return (1);
		}
	}
	return (0);
}
