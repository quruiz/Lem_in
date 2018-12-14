/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   room.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/28 14:51:53 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/28 10:08:50 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lem_in.h"

int		check_room_type(t_lem *box)
{
	t_rlist *tmp;

	if (box->rtype == 0)
		return (0);
	tmp = box->room;
	while (tmp)
	{
		if (tmp->room->type == box->rtype)
		{
			tmp->room->type = 0;
			break ;
		}
		tmp = tmp->next;
	}
	return (1);
}

int		save_type(t_lem *box, t_room *tmp)
{
	if (box->rtype > 0 && check_room_type(box))
		tmp->type = box->rtype;
	else
		tmp->type = 0;
	box->rtype = 0;
	return (1);
}

int		check_room_coor(t_lem *box, uintmax_t x, uintmax_t y, char *name)
{
	t_rlist	*tmp;

	tmp = box->room;
	while (tmp)
	{
		if (x == tmp->room->coor[0] && y == tmp->room->coor[1])
		{
			free(tmp->room->name);
			tmp->room->name = ft_strdup(name);
			return (save_type(box, tmp->room));
		}
		if (ft_strequ(tmp->room->name, name))
		{
			tmp->room->coor[0] = y;
			tmp->room->coor[1] = x;
			return (save_type(box, tmp->room));
		}
		tmp = tmp->next;
	}
	return (0);
}

int		make_room(t_lem *box, char *name, uintmax_t x, uintmax_t y)
{
	t_room	*tmp;

	if (check_room_coor(box, x, y, name))
		return (1);
	if (!(tmp = ft_memalloc(sizeof(t_room))))
		return (free_room(box->room));
	tmp->name = ft_strdup(name);
	tmp->coor[0] = x;
	tmp->coor[1] = y;
	tmp->dist = -1;
	tmp->ant = 0;
	save_type(box, tmp);
	add_room(tmp, &box->room);
	return (1);
}

int		verif_room(t_lem *box, char *line)
{
	char	**split;

	if ((ft_strchr(line, '-') == ft_strrchr(line, '-') && ft_strchr(line, '-')))
	{
		box->step = 3;
		return ((!box->rtype) ? verif_tube(box, line) : 0);
	}
	if (*line == '#')
		return (check_comment(box, line));
	if (*line == 'L')
		return (0);
	if (ft_strchr(line, ' ') && !check_room_format(line))
		return (0);
	split = ft_split_whitespaces(line);
	if (!split[0] || split[3] || !(ft_check_limit(split[1], UINT_LIMIT) &&
		ft_check_limit(split[2], UINT_LIMIT)))
		return (ft_freesplit(split));
	else if (!make_room(box, split[0], ft_atoui(split[1]), ft_atoui(split[2])))
		return (ft_freesplit(split));
	ft_freesplit(split);
	return (1);
}
