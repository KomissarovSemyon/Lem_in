/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:56:25 by mraynor           #+#    #+#             */
/*   Updated: 2019/02/07 13:56:30 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		read_com(t_lemin *lem, int i, int j, int k)
{
	char **com;
	char *room;

	if ((k = ft_gnl(0, &room)) != 1)
		return (k);
	com = ft_strsplit(room, ' ');
	free(room);
	while (com[++i])
	{
		j = 0;
		if ((k = ft_atoi(com[i] + 1)) < 1 || k > lem->cants)
			return (-1);
		while (com[i][++j] <= '9' && com[i][j] >= '0')
			;
		room = ft_strsub(com[i], j + 1, ft_strlen(com[i]) - j - 1);
		add_neigh_to_neigh(&lem->prway[k - 1], find_list(lem->rlist, room));
		if (!lem->prway[k - 1] || !lem->prway[k - 1]->next)
			return (0);
		lem->prway[k - 1]->next->room->status = (lem->prway[k - 1]->next->room
			== lem->start) ? lem->prway[k - 1]->next->room->status - 1 : 0;
		lem->prway[k - 1]->room->status = k;
		free(room);
	}
	del_arr(com);
	return (1);
}

void	find_min(t_list1 *t, int *maxx, int *maxy, t_cf *cf)
{
	cf->minx = t->x;
	cf->miny = t->y;
	*maxx = t->x;
	*maxy = t->y;
	t = t->next;
	while (t)
	{
		if (cf->minx > t->x)
			cf->minx = t->x;
		if (cf->miny > t->y)
			cf->miny = t->y;
		if (*maxx < t->x)
			*maxx = t->x;
		if (*maxy < t->y)
			*maxy = t->y;
		t = t->next;
	}
}

int		close1(t_cf *cf)
{
	int x;

	x = -1;
	if (cf && cf->win)
		mlx_destroy_window(cf->ptr, cf->win);
	if (cf && cf->lem)
	{
		if (cf->lem->prway)
			while (++x < cf->lem->cants)
				if (cf->lem->prway[x])
					del_neight(&cf->lem->prway[x], cf->lem->end);
		del_list(&cf->lem->rlist);
		free(cf->lem->prway);
		free(cf->lem);
	}
	free(cf);
	exit(0);
	return (0);
}

void	line(int a[2], int b[2], t_cf *cf, int col)
{
	int		l;
	float	d[2];
	float	z[2];

	l = FABS(a[0] - b[0]);
	l = (FABS(a[1] - b[1]) > l) ? FABS(a[1] - b[1]) : l;
	if (l == 0)
		return ;
	d[0] = (float)(b[0] - a[0]) / l;
	d[1] = (float)(b[1] - a[1]) / l;
	z[0] = a[0] + cf->sizer / 2;
	z[1] = a[1] + cf->sizer / 2;
	while (l--)
	{
		if ((z[1] >= 0 && z[1] < H_SIZE && z[0] >= 0 && z[0] < W_SIZE &&
		IS_SQRT(z[0], a[0], z[1], a[1], cf->sizer) && IS_SQRT(z[0], b[0], z[1],
		b[1], cf->sizer)) || col == COL_ANT)
		{
			mlx_pixel_put(cf->ptr, cf->win, (int)(z[0]), (int)(z[1]), col);
			mlx_pixel_put(cf->ptr, cf->win, (int)(z[0] + 1), (int)(z[1]), col);
			mlx_pixel_put(cf->ptr, cf->win, (int)(z[0]), (int)(z[1] + 1), col);
		}
		z[0] += d[0];
		z[1] += d[1];
	}
}

void	do_net(t_list1 *t, t_cf *cf, int minx, int miny)
{
	t_neigh		*next;
	t_list1		*now;
	int			col;
	int			a[2];
	int			b[2];

	if (!t || !t->neigh)
		return ;
	next = t->neigh;
	while (next)
	{
		a[0] = CORD_X(t->x, (int)cf->dx, minx);
		a[1] = CORD_Y(t->y, (int)cf->dy, miny);
		b[0] = CORD_X(next->room->x, (int)cf->dx, minx);
		b[1] = CORD_Y(next->room->y, (int)cf->dy, miny);
		line(a, b, cf, FREE_ROOM);
		next = next->next;
	}
	col = (COL_ROOM | (t->status * 30) % 255 << 16 |
	(t->status * 55) % 255 << 8 | (t->status * 15) % 255);
}
