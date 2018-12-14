/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/24 13:28:35 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 17:31:56 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# define UINT_LIMIT "18446744073709551615"

typedef struct		s_lem
{
	struct s_rlist	*room;
	struct s_path	*path;
	uintmax_t		ant;
	uintmax_t		map_size;
	uintmax_t		nb_path;
	char			**map;
	int				step;
	int				rtype;
	int				path_size;
}					t_lem;

typedef struct		s_room
{
	uintmax_t		nb_link;
	uintmax_t		ant;
	uintmax_t		coor[2];
	char			*name;
	int				type;
	int				visit;
	int				dist;
	struct s_rlist	*link;
}					t_room;

typedef struct		s_path
{
	uintmax_t		size;
	char			**moves;
	int				move;
	struct s_rlist	*path;
	struct s_path	*next;
}					t_path;

typedef struct		s_rlist
{
	struct s_room	*room;
	struct s_rlist	*next;
}					t_rlist;

/*
**	Parsing
*/

int					verif_ant(t_lem *box, char *line);
int					verif_room(t_lem *box, char *line);
int					verif_tube(t_lem *box, char *line);
int					add_room(t_room *r, t_rlist **list);
int					find_room(t_rlist *r, char *n, t_room **p);
t_rlist				*find_startend(t_rlist *r, int type);
int					check_comment(t_lem *box, char *line);
int					sort_link_list(t_rlist *r);
int					add_link_to_list(t_room *r, t_rlist **list);
void				rev_list(t_rlist *src, t_rlist **dest);
int					add_path(t_path *p, t_path **list);
int					create_rlist(t_room **r, t_rlist **l);
int					check_room_format(char *line);

/*
**	Algorithm
*/

int					bfs(t_lem *box);
int					find_path(t_lem *box);
void				move_ant(t_lem *box);

/*
**	Destructors
*/

void				free_all(t_lem *box);
int					free_room(t_rlist *r);
void				free_path(t_path *p);
void				free_link(t_rlist *l);
void				rm_room(t_rlist **l, t_room *r);
void				rm_link(t_room *r1, t_room *r2);
void				rlist_delone(t_rlist **l, t_room *target);
int					ultimate_cleaner(t_lem *box);

#endif
