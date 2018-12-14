/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   room.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 18:27:31 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/28 08:12:49 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lem_in.h"

int		add_room(t_room *r, t_rlist **list)
{
	t_rlist	*tmp;

	tmp = *list;
	if (!tmp)
	{
		if (!create_rlist(&r, list))
			return (0);
		return (1);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (!create_rlist(&r, &tmp->next))
		return (0);
	return (1);
}

int		find_room(t_rlist *r, char *n, t_room **p)
{
	t_rlist	*tmp;

	tmp = r;
	while (tmp)
	{
		if (ft_strcmp(tmp->room->name, n) == 0)
		{
			*p = tmp->room;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_rlist	*find_startend(t_rlist *r, int type)
{
	t_rlist	*tmp;
	int		count;

	tmp = r;
	count = 0;
	if (type == 3)
	{
		if ((find_startend(r, 1) != NULL) && (find_startend(r, 2) != NULL))
			return (tmp);
		else
			return (NULL);
	}
	while (tmp)
	{
		if (tmp->room->type == type)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int		add_path(t_path *p, t_path **list)
{
	if (!*list)
	{
		*list = p;
		return (1);
	}
	p->next = *list;
	*list = p;
	return (1);
}

int		check_room_format(char *line)
{
	int		i;

	i = 0;
	while (line[i] != ' ')
		i++;
	if (line[i] == ' ' && line[i + 1] != ' ')
		i++;
	else
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == ' ' && line[i + 1] != ' ')
		i++;
	else
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}
