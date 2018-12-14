/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_ant.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 17:02:45 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 18:45:33 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lem_in.h"

char	*save_move(t_room *r)
{
	char	*tmp;
	char	*ant;

	tmp = NULL;
	ant = ft_uitoa(r->ant);
	tmp = ft_conncat(tmp, "L", 0, 1);
	tmp = ft_conncat(tmp, ant, 1, ft_strlen(ant));
	tmp = ft_conncat(tmp, "-", ft_strlen(tmp), 1);
	tmp = ft_conncat(tmp, r->name, ft_strlen(tmp), ft_strlen(r->name));
	tmp = ft_conncat(tmp, " ", ft_strlen(tmp), 1);
	free(ant);
	return (tmp);
}

int		make_moves_tab(t_lem *box)
{
	int			size;
	t_path		*tmp;

	tmp = box->path;
	while (tmp->next)
		tmp = tmp->next;
	box->path_size = tmp->size;
	size = tmp->size;
	tmp = box->path;
	while (tmp)
	{
		if (!(tmp->moves = ft_memalloc(sizeof(char *) * size + 1)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	print_moves(t_lem *box)
{
	t_path		*path;
	int			limit;
	int			i;

	limit = box->path_size;
	i = 0;
	while (i < limit)
	{
		path = box->path;
		while (path)
		{
			if (path->moves[i])
				ft_putstr(path->moves[i]);
			ft_strdel(&path->moves[i]);
			path = path->next;
		}
		i++;
	}
	ft_putchar('\n');
}

int		move_ant2(t_lem *box, t_path *path, t_rlist *rlist, uintmax_t *ant)
{
	int i;

	i = 0;
	while (rlist)
	{
		if ((rlist->next && rlist->next->room->type == 1) &&
			(*ant <= box->ant && *ant))
		{
			rlist->room->ant = *ant;
			if (*ant && *ant == box->ant)
				*ant = 0;
			else
				*ant += 1;
		}
		else if (rlist->room->type != 1 && rlist->next)
			rlist->room->ant = rlist->next->room->ant;
		if (rlist->room->ant)
			path->moves[i++] = save_move(rlist->room);
		rlist = rlist->next;
	}
	return (i);
}

void	move_ant(t_lem *box)
{
	t_path		*path;
	t_rlist		*rlist;
	int			i;
	int			move;
	uintmax_t	ant_count;

	ant_count = 1;
	if (!make_moves_tab(box))
		return ;
	while (1)
	{
		move = 0;
		path = box->path;
		while (path)
		{
			rlist = path->path;
			i = 0;
			move += move_ant2(box, path, rlist, &ant_count);
			path = path->next;
		}
		if (move)
			print_moves(box);
		else
			break ;
	}
}
