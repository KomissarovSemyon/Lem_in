/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:50:59 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/09 14:31:24 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	del_neight(t_neigh **t, t_list1 *end)
{
	t_neigh		*d;
	t_neigh		*d1;

	d = *t;
	while (d)
	{
		d1 = d->next;
		if (d->room != end && d->room)
			d->room->status = 0;
		free(d);
		d = d1;
	}
	*t = NULL;
}

void	del_list(t_list1 **l)
{
	t_list1		*t;
	t_list1		*t1;
	t_neigh		*d;
	t_neigh		*d1;

	t = *l;
	while (t)
	{
		t1 = t->next;
		d = t->neigh;
		while (d)
		{
			d1 = d->next;
			free(d);
			d = d1;
		}
		free(t->name);
		free(t);
		t = t1;
	}
	*l = NULL;
}

int		add_list(t_list1 **st, char *name, int x, int y)
{
	t_list1		*t;
	t_list1		*t1;

	if (!name || !(t = (t_list1 *)ft_memalloc(sizeof(t_list1))))
		return (0);
	t->name = name;
	t->x = x;
	t->y = y;
	if (!(*st))
		*st = t;
	else
	{
		t1 = *st;
		while (t1->next)
			t1 = t1->next;
		t1->next = t;
	}
	return (1);
}

int		add_neigh(t_list1 *base, t_list1 *add)
{
	t_neigh		*n;
	t_neigh		*n1;

	if (!(n = (t_neigh *)malloc(sizeof(t_neigh))))
		return (0);
	n->room = add;
	n->next = NULL;
	if (!base->neigh)
		base->neigh = n;
	else
	{
		n1 = base->neigh;
		while (n1->next)
			n1 = n1->next;
		n1->next = n;
	}
	return (1);
}

int		add_neigh_to_neigh(t_neigh **base, t_list1 *add)
{
	t_neigh		*n;

	if (!(n = (t_neigh *)ft_memalloc(sizeof(t_neigh))))
		return (0);
	n->room = add;
	n->next = NULL;
	if (*base == NULL)
		*base = n;
	else
	{
		n->next = *base;
		*base = n;
	}
	return (1);
}
