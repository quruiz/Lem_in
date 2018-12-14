/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   del_list.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 18:21:31 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 21:15:41 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lem_in.h"

void	rlist_delone(t_rlist **l, t_room *target)
{
	t_rlist *tmp1;
	t_rlist *tmp2;

	tmp1 = *l;
	tmp2 = tmp1->next;
	if (tmp1->room == target)
	{
		*l = (((*l)->next == NULL) ? NULL : (*l)->next);
		free(tmp1);
		return ;
	}
	while (tmp2->room != target)
	{
		tmp1 = tmp1->next;
		tmp2 = tmp1->next;
	}
	while (tmp2->next != NULL)
	{
		tmp2->room = tmp2->next->room;
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	free(tmp2);
	tmp1->next = NULL;
}

void	rm_link(t_room *r1, t_room *r2)
{
	rlist_delone(&r1->link, r2);
	rlist_delone(&r2->link, r1);
	r1->nb_link--;
	r2->nb_link--;
}

void	rm_room(t_rlist **l, t_room *r)
{
	t_rlist	*tmp;

	tmp = NULL;
	if (r->link)
		tmp = r->link;
	while (tmp)
	{
		rm_link(r, tmp->room);
		if (r->nb_link == 0)
			break ;
		tmp = tmp->next;
	}
	rlist_delone(l, r);
	free(r->name);
	free(r);
}

int		ultimate_cleaner(t_lem *box)
{
	t_rlist	*tmp;
	int		i;

	tmp = box->room;
	i = 0;
	while (tmp)
	{
		if (tmp->room->nb_link == 1 && tmp->room->type == 0)
		{
			rm_room(&box->room, tmp->room);
			return (1);
		}
		else
			tmp = tmp->next;
	}
	return (i);
}
