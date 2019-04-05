/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizual2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:55:16 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/09 14:55:21 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	do_col_net(t_cf *cf, int n, int i)
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
