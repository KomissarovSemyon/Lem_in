/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 20:58:17 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/09 14:15:52 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			del_first(t_neigh **base, t_list1 *end)
{
	t_neigh *t;

	t = (*base);
	(*base) = (*base)->next;
	if (t->room != end)
		t->room->status = 0;
	free(t);
	return (0);
}

void		init_way(t_lemin *t)
{
	int			i;
	int			min;
	t_neigh		*t1;

	t1 = t->end->neigh;
	min = t1->room->wayst;
	while (t1)
	{
		if (t1->room->wayst != 0 < min)
			min = t1->room->wayst;
		t1 = t1->next;
	}
	t1 = t->end->neigh;
	while (t1)
	{
		if (t1->room->wayst != 0 && min + t->cants > t1->room->wayst)
			t->cways++;
		t1 = t1->next;
	}
	i = -1;
	t->ways = (t_neigh **)ft_memalloc(sizeof(t_neigh *) * t->cways * 2);
	while (++i < t->cways)
		add_neigh_to_neigh(&t->ways[i * 2], t->end);
}

void		free_all(t_lemin *lem, int i)
{
	int x;

	if (i == 1)
		write(1, "Error\n", 6);
	if (lem)
	{
		if (lem->prway)
			free(lem->prway);
		x = -1;
		if (lem->ways)
		{
			while (++x < lem->cways * 2)
				if (lem->ways[x])
					del_neight(&lem->ways[x], lem->end);
			free(lem->ways);
		}
		if (lem->rlist)
			del_list(&lem->rlist);
		free(lem->c);
		ft_lstdel(&(lem->buff_head), NULL);
		free(lem);
	}
	exit(0);
}

void		print_ant(int ant, char *name)
{
	ft_putstr("L");
	ft_putnbr(ant + 1);
	ft_putstr("-");
	ft_putstr(name);
	ft_putstr(" ");
}

void		print_buff(t_list *head)
{
	while (head)
	{
		ft_putendl(head->content);
		head = head->next;
	}
}
