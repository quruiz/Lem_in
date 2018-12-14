/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 18:32:33 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 16:26:26 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lem_in.h"

int		check_startend_path(t_lem *box)
{
	t_rlist		*end;
	t_rlist		*start;

	if ((!(end = find_startend(box->room, 2))) ||
		(!(start = find_startend(box->room, 1))))
		return (0);
	if (!end->room->link || !end->room->link)
		return (0);
	else
		return (1);
}

void	init_bfs(t_lem *box)
{
	t_rlist *tmp;

	tmp = box->room;
	while (tmp)
	{
		if (tmp->room->link != NULL)
		{
			sort_link_list(tmp);
			tmp = tmp->next;
		}
		else
		{
			rm_room(&box->room, tmp->room);
			tmp = box->room;
		}
	}
}

int		bfs(t_lem *box)
{
	t_rlist *list;
	t_rlist *tmp;
	t_rlist *tmpr;

	list = NULL;
	init_bfs(box);
	if (!(tmpr = find_startend(box->room, 1)))
		return (0);
	add_room(tmpr->room, &list);
	list->room->dist = 0;
	list->room->visit = 1;
	while (list)
	{
		add_link_to_list(list->room, &list);
		if (list->room->nb_link < 2 && list->room->type == 0)
			rm_room(&box->room, list->room);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	while (ultimate_cleaner(box))
		;
	if (check_startend_path(box) == 0 || find_path(box) == 0)
		return (0);
	return (1);
}
