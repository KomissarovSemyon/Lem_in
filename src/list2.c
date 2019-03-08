/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraynor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:27:06 by mraynor           #+#    #+#             */
/*   Updated: 2019/02/02 19:27:09 by mraynor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			is_have(t_neigh *no, t_list1 *room)
{
	if (room == NULL)
		return (0);
	while (no)
	{
		if (no->room == room)
			return (1);
		no = no->next;
	}
	return (0);
}

t_list1		*find_list(t_list1 *l, const char *name)
{
	if (l == NULL)
		return (NULL);
	if (ft_strcmp(l->name, name) == 0)
		return (l);
	return (find_list(l->next, name));
}

int			find_len_st(t_lemin *lem, t_list1 *l, int i)
{
	t_neigh		*k;

	if ((l->wayst <= i && l->wayst != 0) || (l == lem->start && i != 1))
		return (1);
	if (l == lem->end)
	{
		l->wayst = (i > l->wayst) ? i : l->wayst;
		return (1);
	}
	k = l->neigh;
	l->wayst = i;
	while (k)
	{
		find_len_st(lem, k->room, i + 1);
		k = k->next;
	}
	return (1);
}

int			len_way(t_neigh *t)
{
	if (!t)
		return (0);
	return (len_way(t->next) + 1);
}

void	del_arr(char **com)
{
	int i;

	i = -1;
	while (com[++i])
		free(com[i]);
	free(com);
}
