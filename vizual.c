/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 20:44:51 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/08 19:59:27 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		do_col_net(t_cf *cf, int n, int i)
{
	t_list1		*t;
	int			col;
	int			count;
	int			a[2];
	int			b[2];

	count = (n == -1) ? cf->lem->cants : n;
	while (++i < count)
		if (cf->lem->prway[i] && cf->lem->prway[i]->next)
		{
			t = cf->lem->prway[i]->room;
			if (n == -1)
				col = (COL_ROOM | (t->status * 30) % 255 << 16 |
				(t->status * 55) % 255 << 8 | (t->status * 17) % 255);
			else
				col = (COL_ROOM | (i * 30) % 255 << 16 |
				(i * 55) % 255 << 8 | (i * 67) % 255);
			a[0] = CORD_X(t->x, (int)cf->dx, cf->minx);
			a[1] = CORD_Y(t->y, (int)cf->dy, cf->miny);
			b[0] = CORD_X(cf->lem->prway[i]->next->room->x, (int)cf->dx,
				cf->minx);
			b[1] = CORD_Y(cf->lem->prway[i]->next->room->y, (int)cf->dy,
			cf->miny);
			line(a, b, cf, col);
		}
}

void	drawin(t_list1 *t, t_cf *cf)
{
	int		col;
	int		y;
	int		i;
	char	*v;

	mlx_string_put(cf->ptr, cf->win, CORD_X(t->x, cf->dx, cf->minx),
		CORD_Y(t->y, cf->dy, cf->miny), FREE_STRING, t->name);
	if (t->status != 0)
	{
		col = ((t->status * 30) % 255 << 16 | (t->status * 11) % 255 << 8
			| (t->status * 40) % 255);
		v = ft_itoa(t->status);
		mlx_string_put(cf->ptr, cf->win, CORD_X(t->x, cf->dx, cf->minx)
			+ cf->sizer / 2 - RAD_ANT, CORD_Y(t->y, cf->dy, cf->miny) +
			cf->sizer / 2 - 4, col, v);
		free(v);
	}
}

void	draw(t_list1 *t, t_cf *cf)
{
	int		i;
	int		y;
	int		col;
	char	*v;

	col = COL_ROOM;
	while (t)
	{
		i = -1;
		do_net(t, cf, cf->minx, cf->miny);
		col = (COL_ROOM | (t->status * 30) % 255 << 16 |
				(t->status * 55) % 255 << 8 | (t->status * 17) % 255);
		while (++i < cf->sizer)
		{
			y = -1;
			while (++y < cf->sizer)
				mlx_pixel_put(cf->ptr, cf->win, i + CORD_X(t->x, cf->dx,
					cf->minx), y + CORD_Y(t->y, cf->dy, cf->miny),
					t->status > 0 ? col : FREE_ROOM);
		}
		drawin(t, cf);
		t = t->next;
	}
	do_col_net(cf, -1, -1);
}

void	init_lem(t_cf *cf)
{
	int		max[2];
	int		i;

	i = -1;
	cf->lem->start->status = cf->lem->cants;
	cf->lem->prway = (t_neigh **)ft_memalloc(sizeof(t_neigh *) *
		cf->lem->cants);
	while (++i < cf->lem->cants)
		add_neigh_to_neigh(&cf->lem->prway[i], cf->lem->start);
	find_min(cf->lem->rlist, &max[0], &max[1], cf);
	cf->sizer = SIZE_ROOM * cf->scellr;
	if (max[0] != cf->minx)
		cf->dx = (W_SIZE - BORD_X) / (max[0] - cf->minx);
	if (max[1] != cf->miny)
		cf->dy = (H_SIZE - BORD_Y) / (max[1] - cf->miny);
	draw(cf->lem->rlist, cf);
}

int		key_press(int but, t_cf *cf)
{
	int i;

	if (but == 49 && !cf->onlway)
	{
		i = -1;
		while (++i < cf->lem->cants)
			if (cf->lem->prway[i] && cf->lem->prway[i]->room == cf->lem->end)
				del_neight(&cf->lem->prway[i], cf->lem->end);
		if (read_com(cf->lem, -1, 0, 0) == 1)
			draw(cf->lem->rlist, cf);
	}
	if (but == 53)
		close1(cf);
	return (0);
}

void	vizual_way(t_cf *cf)
{
	int		l;
	int		i;

	init_lem(cf);
	cf->onlway = 1;
	read_com(cf->lem, -1, 0, 0);
	l = -1;
	while (cf->lem->prway[++l]->room != cf->lem->start)
		;
	do_col_net(cf, l, -1);
	while (read_com(cf->lem, -1, 0, 0) == 1)
		do_col_net(cf, l, -1);
}

int		main(int a, char **c)
{
	t_cf	*cf;

	if (!(cf = (t_cf *)ft_memalloc(sizeof(t_cf))) ||
		!(cf->lem = (t_lemin *)ft_memalloc(sizeof(t_lemin))) ||
		read_input(cf->lem, 0) == 1 || !cf->lem->rlist)
	{
		printf("Error\n");
		close1(cf);
		return (0);
	}
	cf->scell = 1;
	cf->scellr = 1;
	cf->ptr = mlx_init();
	cf->win = mlx_new_window(cf->ptr, W_SIZE, H_SIZE, "checker");
	if (a > 1 && !ft_strcmp(c[1], "-w"))
		vizual_way(cf);
	else
		init_lem(cf);
	mlx_hook(cf->win, 17, 4, close1, cf);
	mlx_hook(cf->win, 2, 1, key_press, cf);
	mlx_loop(cf->ptr);
	return (0);
}

