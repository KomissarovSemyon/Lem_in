/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:25:46 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/08 20:56:33 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"
# include <stdio.h>
# include "mlx.h"
# define W_SIZE 1500
# define H_SIZE 1300
# define SIZE_ROOM 60
# define MIN_SIZE 5
# define RAD_ANT 20
# define COL_ANT 0x7f8e3f
# define COL_NUM 0x7CFC7C
# define COL_ROOM 0x6B8E23
# define COL_STRING 0xf2af00
# define FREE_ROOM 0x008B8B
# define FREE_STRING 0x8FBC8F
# define BORD_X 300
# define BORD_Y 200
# define CAN(x) (x > 100) ? 100 : x
# define FABS(x) (x < 0) ? (x * (-1)) : x
# define CORD_X(x, dx, minx) BORD_X / 2 + dx * (x - minx)
# define CORD_Y(y, dy, miny) BORD_Y / 2 + dy * (y - miny)
# define IS_SQRT(x, x1, y, y1, h) !(x < x1 + h && y < y1 + h && x > x1 && y > y1)

typedef struct s_list1	t_list1;
typedef struct	s_neigh
{
	t_list1			*room;
	struct s_neigh	*next;
}				t_neigh;

struct			s_list1
{
	char			*name;
	int				status;
	int				wayst;
	int				x;
	int				y;
	struct s_list1	*next;
	t_neigh			*neigh;
};

typedef struct	s_lemin
{
	t_list1			*start;
	t_list1			*end;
	t_list1			*rlist;
	t_neigh			**ways;
	t_neigh			**prway;
	t_list			*buff_head;
	t_list			*buff_tail;
	int				*c;
	int				count;
	int				cways;
	int				cants;
}				t_lemin;

typedef struct	s_cf
{
	t_lemin			*lem;
	void			*win;
	void			*ptr;
	int				sizer;
	int				scell;
	float			scellr;
	char			onlway;
	float			dx;
	float			dy;
	int				miny;
	int				minx;
}				t_cf;

void			find_len(t_lemin *lem, t_list1 *l, int i, int num);
void			init_way(t_lemin *t);
void			del_neight(t_neigh **t, t_list1 *end);
void			del_list(t_list1 **l);
t_list1			*find_first_way_new(t_neigh *t1, int count, t_lemin *lem,
					t_neigh *no);
int				find_other_way(t_lemin *lem, int let, int now, t_list1 *no);
int				del_first(t_neigh **base, t_list1 *end);
t_list1			*ret_last(t_neigh *base);
int				add_neigh_to_neigh(t_neigh **base, t_list1 *add);
int				len_way(t_neigh *t);
void			find_den_room(t_list1 *l, t_lemin *lem);
int				is_have(t_neigh *no, t_list1 *room);
void			free_all(t_lemin *lem);
void			print_ant(int ant, char *name);
int				ant_way(t_lemin *lem, int en, int i);
t_list1			*find_list(t_list1 *l, const char *name);
void			print_buff(t_list *head);
void			init_ant(t_lemin *t);
int				add_list(t_list1 **st, char *name, int x, int y);
int				add_neigh(t_list1 *base, t_list1 *add);
int				read_input(t_lemin *lem, char *name);
int				read_com(t_lemin *lem, int i, int j, int k);
void			find_min(t_list1 *t, int *maxx, int *maxy, t_cf *cf);
int				close1(t_cf *cf);
void			line(int a[2], int b[2], t_cf *cf, int col);
void			do_net(t_list1	*t, t_cf *cf, int minx, int miny);
int				find_len_st(t_lemin *lem, t_list1 *l, int i);
void			del_arr(char **com);
int				ft_xatoi(const char *str);
void			parse_neigh(t_lemin *lem, char *line, int *last_type,
					int *type);
void			parse_room(t_lemin *lem, char *line, int *last_type, int *type);
int				get_type(char *line);
int				add_room_to_lem(t_lemin *lem, char *line, int room_type);
void			parse_ants(t_lemin *lem, char *line, int *last_type);
int				add_list_unique(t_list1 **st, char *n, int x, int y);
int				connect_to_list(t_lemin *lem, char *name, int room_type);
#endif
