/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 16:52:53 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/08 21:05:20 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		print_st(t_lemin *lem, int k)
{
	int		ant;
	int		i;

	ant = 0;
	i = -1;
	while (++i < lem->cways && k < lem->cants && lem->count > ant)
		if (lem->ways[i * 2] && lem->c[ant])
		{
			lem->prway[k++] = lem->ways[i * 2]->next;
			lem->c[ant++]--;
		}
		else if (!lem->c[ant])
			ant++;
	ant = -1;
	i = 0;
	while (++ant < lem->cants)
		if (lem->prway[ant])
		{
			print_ant(ant, lem->prway[ant]->room->name);
			lem->prway[ant] = lem->prway[ant]->next;
		}
		else if (++i == lem->cants)
			return (-1);
	ft_putstr("\n");
	return (k);
}

int		sort_arr(t_lemin *lem, int *arr, int n, int c)
{
	int		k;
	int		i;

	k = -1;
	while (++k < n - 1)
	{
		i = -1;
		while (++i < n - 1 - k)
			if (arr[i] > arr[i + 1])
			{
				c = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = c;
			}
	}
	k = 0;
	i = lem->cants;
	while (i != 0 && k != n - 1)
	{
		i -= ((arr[k + 1] - arr[k]) * (k + 1));
		if (++k && i < 0 && k--)
			break ;
	}
	lem->count = k + 1;
	return (k);
}

void	find_way(t_neigh **ways, t_lemin *lem, int *arr, int min)
{
	int		summ;
	int		i;
	int		k;
	int		count;

	summ = 0;
	lem->c = (int *)ft_memalloc(4 * (lem->count));
	count = 0;
	i = -1;
	while (++i < lem->cways)
		if ((k = len_way(ways[i * 2])) - min > arr[lem->count - 1] || k == 0 ||
			count >= lem->count)
			del_neight(&ways[i * 2], lem->end);
		else
		{
			lem->c[count] = arr[lem->count - 1] - k + min;
			summ += lem->c[count++];
		}
	count = (lem->cants - summ) % (lem->count);
	summ = (lem->cants - summ) / (lem->count);
	i = -1;
	k = 0;
	while (++i < lem->cways)
		if (ways[i * 2])
			lem->c[k++] += summ + ((count-- > 0) ? 1 : 0);
}

void	do_short(t_neigh **ways, t_lemin *lem, int min, int i)
{
	int		count;
	int		*arr;
	int		k;

	arr = (int *)ft_memalloc(4 * lem->cways);
	count = 0;
	while (++i < lem->cways)
	{
		if ((k = len_way(ways[i * 2])) > 0)
			arr[count++] = k;
		if ((min == 0 || min > k) && k != 0)
			min = k;
	}
	if (count == 1 && (lem->c = arr))
	{
		lem->c[0] = lem->cants;
		return ;
	}
	i = -1;
	k = 0;
	while (++i < count && ++k)
		arr[k - 1] = arr[k - 1] - min;
	sort_arr(lem, arr, count, 0);
	find_way(ways, lem, arr, min);
	free(arr);
}

int		main()
{
	t_lemin		*lem;
	int			x;

	if (!(lem = (t_lemin *)ft_memalloc(sizeof(t_lemin))) ||
		read_input(lem, 0) == -1 || !find_len_st(lem, lem->start, 1)
		|| lem->end->wayst == 0)
	{
		printf("Error\n");
		free_all(lem);
	}
	print_buff(lem->buff_head);
	write(1, "\n", 1);
	lem->end->status = 1;
	lem->count = 1;
	init_way(lem);
	while(ant_way(lem, 0, -1) != 1)
		;
	if (!(lem->prway = (t_neigh **)ft_memalloc(sizeof(t_neigh *) * lem->cants)))
	{
		printf("Error\n");
		free_all(lem);
	}
	do_short(lem->ways, lem, 0, -1);
	x = 0;
	while (x > -1)
		x = print_st(lem, x);
	free_all(lem);
	return (0);
}
