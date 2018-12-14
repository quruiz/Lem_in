/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 18:23:47 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 16:41:00 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lem_in.h"

void	swap_list(t_rlist **l1, t_rlist **l2)
{
	t_room *tmp;

	tmp = (*l1)->room;
	(*l1)->room = (*l2)->room;
	(*l2)->room = tmp;
}

int		sort_link_list(t_rlist *r)
{
	t_rlist *tmpl1;
	t_rlist *tmpl2;

	tmpl1 = r->room->link;
	while (tmpl1->next)
	{
		if (tmpl1->room->nb_link <= tmpl1->next->room->nb_link)
			tmpl1 = tmpl1->next;
		else
		{
			tmpl2 = tmpl1->next;
			swap_list(&tmpl1, &tmpl2);
			tmpl1 = r->room->link;
		}
	}
	return (0);
}

void	rev_list(t_rlist *src, t_rlist **dest)
{
	if (src->next)
		rev_list(src->next, dest);
	add_room(src->room, dest);
	free(src);
	src = NULL;
}

int		create_rlist(t_room **r, t_rlist **l)
{
	t_rlist		*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_rlist))))
		return (0);
	tmp->next = NULL;
	tmp->room = *r;
	*l = tmp;
	return (1);
}

int		add_link_to_list(t_room *r, t_rlist **list)
{
	t_rlist *tmp;
	int		i;

	tmp = r->link;
	while (tmp)
	{
		i = 1;
		if (tmp->room->visit == 1 && tmp->room->type == 0 &&
			(tmp->room->nb_link > 2 && r->nb_link > 2))
		{
			i = (tmp->next) ? 1 : 0;
			rm_link(tmp->room, r);
			tmp = (!i) ? r->link : NULL;
		}
		else if (tmp->room->dist == -1)
		{
			tmp->room->dist = (r->dist + 1);
			tmp->room->visit = 1;
			add_room(tmp->room, list);
		}
		tmp = (tmp != NULL) ? tmp->next : NULL;
	}
	r->visit = 2;
	return (1);
}
