/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/23 14:15:45 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 18:50:40 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	init_box(t_lem *box)
{
	box->room = NULL;
	box->ant = 0;
	box->path = NULL;
	box->map = NULL;
	box->map_size = 0;
	box->step = 1;
	box->rtype = 0;
	box->nb_path = 0;
}

int		lem_parse(t_lem **b)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if ((*b)->step == 1)
		{
			if (!line || !verif_ant(*b, line))
				return (ft_free_line(&line, 0));
		}
		else if ((*b)->step == 2)
		{
			if (!line || !verif_room(*b, line))
				return (ft_free_line(&line, 0));
		}
		else if ((*b)->step == 3)
		{
			if (!line || !verif_tube(*b, line))
				return (ft_free_line(&line, 1));
		}
		(*b)->map = ft_add_line_to_tab((*b)->map, line, (*b)->map_size++);
	}
	return (((*b)->step != 3 || find_startend((*b)->room, 3) == NULL) ? 0 : 1);
}

int		main(void)
{
	t_lem	*box;

	if (!(box = malloc(sizeof(t_lem))))
	{
		ft_putstr("ERROR\n");
		return (0);
	}
	init_box(box);
	if (!lem_parse(&box) || !bfs(box))
	{
		free_all(box);
		ft_putstr("ERROR\n");
		return (0);
	}
	ft_putsplit(box->map);
	ft_putchar('\n');
	move_ant(box);
	free_all(box);
	return (1);
}
