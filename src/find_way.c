/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:08:42 by mraynor           #+#    #+#             */
/*   Updated: 2019/02/09 17:08:48 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			is_ok(int x, t_neigh *t1, t_lemin *lem)
{
	if ((x == -1 || x > t1->room->wayst || t1->room == lem->start)
			&& t1->room->wayst != 0 && t1->room != lem->end)
		return (1);
	return (0);
}

t_list1		*find_first_way_new(t_neigh *t1, int count, t_lemin *lem,
	t_neigh *no)
{
	int			min[2];
	t_list1		*room[2];

	min[0] = -1;
	min[1] = -1;
	room[0] = NULL;
	room[1] = NULL;
	while (t1)
	{
		if (is_ok(min[0], t1, lem) && t1->room->status == 0 && !
			is_have(no, t1->room))
		{
			room[0] = t1->room;
			min[0] = t1->room->wayst;
		}
		if (is_ok(min[1], t1, lem))
		{
			room[1] = t1->room;
			min[1] = t1->room->wayst;
		}
		t1 = t1->next;
	}
	if (min[0] - min[1] < count + 1 && min[0] != -1)
		return (room[0]);
	return ((!is_have(no, room[1])) ? room[1] : NULL);
}

int			way(t_lemin *lem, int let, int i, t_list1 *no)
{
	t_neigh		*k1;
	t_list1		*room1;

	k1 = lem->ways[let - 1];
	while (i && k1 && k1->room != no)
		k1 = k1->next;
	while ((k1 = k1->next))
		if ((room1 = find_first_way_new(k1->room->neigh, CAN(lem->cants), lem,
		lem->ways[let])) && room1->status == 0 && !is_have(lem->ways[let],
		room1))
			break ;
	if (k1 == NULL || k1->room == lem->end)
		return (0);
	while (i && lem->ways[let - 1] && lem->ways[let - 1]->room != no)
		del_first(&lem->ways[let - 1], lem->end);
	(i) ? del_first(&lem->ways[let - 1], lem->end) : 0;
	while (lem->ways[let - 1] && lem->ways[let - 1] != k1)
	{
		lem->ways[let - 1]->room->status = 0;
		add_neigh_to_neigh(&lem->ways[let], lem->ways[let - 1]->room);
		del_first(&lem->ways[let - 1], lem->end);
	}
	room1->status = (room1 != lem->start) ? let : room1->status;
	add_neigh_to_neigh(&lem->ways[let - 1], room1);
	return (1);
}

int			find_other_way(t_lemin *lem, int let, int now, t_list1 *no)
{
	if (way(lem, now + 1, 0, no))
		return (0);
	if (way(lem, let, 1, no))
		return (0);
	del_neight(&lem->ways[now], lem->end);
	return (1);
}

int			ant_way(t_lemin *lem, int en, int i)
{
	t_list1		*k;

	while (++i < lem->cways)
		if (lem->ways[i * 2] && lem->ways[i * 2]->room != lem->start)
		{
			k = find_first_way_new(lem->ways[i * 2]->room->neigh,
				CAN(lem->cants), lem, lem->ways[i * 2 + 1]);
			if (k == NULL || k->status != 0 || is_have(lem->ways[i * 2 + 1], k))
			{
				if (!k || lem->ways[i * 2]->room == lem->end || k == lem->end)
					del_neight(&lem->ways[i * 2], lem->end);
				else
					find_other_way(lem, k->status, i * 2, k);
			}
			else
			{
				add_neigh_to_neigh(&lem->ways[i * 2], k);
				if (k != lem->start)
					k->status = i * 2 + 1;
			}
		}
		else if (++en == lem->cways)
			return (1);
	return (0);
}
