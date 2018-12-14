/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_path.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:23:26 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 18:46:41 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lem_in.h"

/*
**	room->visit
**
**	0 = Never visited
**	1 = In waiting list
**	2 = Visited
**	3 = Used in a path
*/

int		solve(t_lem *box, t_rlist *list, t_path *p)
{
	t_rlist	*tmp;

	tmp = list->room->link;
	if (list->room->type == 1)
		return (1);
	while (tmp)
	{
		if (tmp->room->visit == 2 && tmp->room->dist <= list->room->dist)
		{
			if (list->room->type == 0)
				list->room->visit = 3;
			add_room(tmp->room, &list);
			p->size++;
			if (!p->size && tmp->room->type == 1)
				return (1);
			if (solve(box, list->next, p))
				return (1);
			rlist_delone(&list, tmp->room);
			if (list->room->type == 0)
				list->room->visit = 2;
			p->size--;
		}
		tmp = tmp->next;
	}
	return (0);
}

int		find_path(t_lem *box)
{
	t_path	*tmp;
	t_rlist	*end;

	while (1)
	{
		if ((!(end = find_startend(box->room, 2))) ||
			(!(tmp = ft_memalloc(sizeof(t_path)))))
			return (0);
		create_rlist(&end->room, &tmp->path);
		if (solve(box, tmp->path, tmp))
		{
			box->nb_path++;
			add_path(tmp, &box->path);
			if (tmp->size == 1)
				return (1);
			tmp = NULL;
		}
		else
		{
			free_link(tmp->path);
			free(tmp);
			return (box->nb_path == 0 ? 0 : 1);
		}
	}
}
