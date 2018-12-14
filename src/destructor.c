/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   destructor.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/05 13:10:55 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 11:51:34 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	free_all(t_lem *box)
{
	if (box->map)
		ft_freesplit(box->map);
	if (box->path)
		free_path(box->path);
	if (box->room)
		free_room(box->room);
	free(box);
}

void	free_link(t_rlist *l)
{
	t_rlist	*tmp1;
	t_rlist	*tmp2;

	tmp1 = l;
	tmp2 = NULL;
	if (tmp1->next)
	{
		while (tmp1->next)
		{
			tmp2 = tmp1->next;
			free(tmp1);
			tmp1 = tmp2;
		}
	}
	free(tmp1);
}

int		free_room(t_rlist *r)
{
	t_rlist	*tmp1;
	t_rlist	*tmp2;

	tmp1 = r;
	tmp2 = NULL;
	if (tmp1->next)
	{
		while (tmp1->next)
		{
			tmp2 = tmp1->next;
			if (tmp1->room->link)
				free_link(tmp1->room->link);
			free(tmp1->room->name);
			free(tmp1->room);
			free(tmp1);
			tmp1 = tmp2;
		}
	}
	if (tmp1->room->link)
		free_link(tmp1->room->link);
	free(tmp1->room->name);
	free(tmp1->room);
	free(tmp1);
	return (0);
}

void	free_path(t_path *p)
{
	t_path	*tmp1;
	t_path	*tmp2;

	tmp1 = p;
	tmp2 = NULL;
	if (tmp1->next)
	{
		while (tmp1->next)
		{
			tmp2 = tmp1->next;
			free_link(tmp1->path);
			free(tmp1->moves);
			free(tmp1);
			tmp1 = tmp2;
		}
	}
	free_link(tmp1->path);
	free(tmp1->moves);
	free(tmp1);
}
