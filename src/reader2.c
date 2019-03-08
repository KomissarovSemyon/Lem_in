/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:33:15 by amerlon-          #+#    #+#             */
/*   Updated: 2019/03/06 23:16:25 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

int			ft_xatoi(const char *str)
{
	int				res;
	int				sign;
	int				i;

	sign = 1;
	res = 0;
	i = 0;
	str[i] == '-' ? sign = -1 : (0);
	str[i] == '+' ? sign = 1 : (0);
	str[i] == '+' || str[i] == '-' ? i++ : (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res * 10 / 10 != res ||
			(res * 10 + str[i] - '0') % 10 != str[i] - '0')
			return (0);
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (sign * res);
}

static void	set_list(t_list1 *t, char *n, int x, int y)
{
	t->name = n;
	t->x = x;
	t->y = y;
}

int			add_list_unique(t_list1 **st, char *n, int x, int y)
{
	t_list1 *l[3];

	if (!n || !(l[0] = (t_list1 *)ft_memalloc(sizeof(t_list1))))
		return (-1);
	set_list(l[0], n, x, y);
	if (!(*st))
		*st = l[0];
	else
	{
		l[1] = *st;
		l[2] = NULL;
		while (l[1])
			if (ft_strcmp(l[1]->name, n) == 0 || (l[1]->x == x && l[1]->y == y))
			{
				free(l[0]);
				return (-1);
			}
			else
			{
				l[2] = l[1];
				l[1] = l[1]->next;
			}
		l[2]->next = l[0];
	}
	return (1);
}

int			connect_to_list(t_lemin *lem, char *name, int room_type)
{
	t_list1 *now;
	t_list1 *t;

	t = NULL;
	now = lem->rlist;
	while (now)
	{
		if (ft_strcmp(now->name, name) == 0)
			t = now;
		now = now->next;
	}
	if (!t)
		return (-1);
	if (room_type == 1)
		lem->start = t;
	else if (room_type == 2)
		lem->end = t;
	return (1);
}

void		parse_ants(t_lemin *lem, char *line, int *last_type)
{
	*last_type = 2;
	lem->cants = ft_xatoi(line);
}
