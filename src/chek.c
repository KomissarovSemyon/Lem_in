/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 23:42:04 by mraynor           #+#    #+#             */
/*   Updated: 2019/03/08 20:00:41 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_chek(t_lemin *lem, int i)
{
	int x;

	x = -1;
	if (i == -2)
		write(1, "KO(\n", 4);
	else if (i == -1)
		write(1, "Error\n", 6);
	else
		write(1, "OK)\n", 4);
	if (lem)
	{
		if (lem->prway)
			while (++x < lem->cants)
				if (lem->prway[x])
					del_neight(&lem->prway[x], lem->end);
		free(lem->prway);
		ft_lstdel(&(lem->buff_head), NULL);
		del_list(&lem->rlist);
		free(lem);
	}
	exit(0);
}

int		littel_free(char **com, char *room, t_lemin *lem, int i)
{
	free(room);
	if (i != 0 && i != -1)
		del_arr(com);
	if (i == 0 || i == -1)
		return (i);
	if (i == -2)
		free_chek(lem, i);
	return (0);
}

int		chek_par(t_lemin *lem, char **com, int i, int *arr)
{
	int		j;
	int		k;

	j = 0;
	k = ft_atoi(com[i] + 1);
	if (k < 1 || k > lem->cants)
		littel_free(com, NULL, lem, -2);
	arr[i] = k;
	k = -1;
	while (++k < i)
		if (arr[k] == arr[i])
			littel_free(com, NULL, lem, -2);
	while (com[i][++j] <= '9' && com[i][j] >= '0')
		;
	return (j);
}

int		chec(t_lemin *lem, int line, int i, int j)
{
	char	**com;
	char	*room;
	t_neigh	*n;
	int		arr[lem->cants];

	com = NULL;
	if ((j = ft_gnl(0, &room)) != 1)
		return (littel_free(com, room, lem, j));
	com = ft_strsplit(room, ' ');
	while (com[++i])
	{
		free(room);
		if ((j = chek_par(lem, com, i, arr)) == -2 ||
		!(room = ft_strsub(com[i], j + 1, ft_strlen(com[i]) - j - 1)))
			littel_free(com, room, lem, -2);
		n = lem->prway[arr[i] - 1]->room->neigh;
		while (n && ft_strcmp(n->room->name, room))
			n = n->next;
		if (!n || (n->room->status == line && n->room != lem->end))
			littel_free(com, room, lem, -2);
		n->room->status = line;
		add_neigh_to_neigh(&lem->prway[arr[i] - 1], n->room);
	}
	littel_free(com, room, lem, 3);
	return (1);
}

int		main(void)
{
	t_lemin		*lem;
	int			x;
	int			i;

	if (!(lem = (t_lemin *)ft_memalloc(sizeof(t_lemin))) ||
		read_input(lem, 0) == 0 || !lem->rlist || !(lem->prway =
		(t_neigh **)ft_memalloc(sizeof(t_neigh *) * lem->cants)))
		free_chek(lem, -1);
	x = -1;
	while (++x < lem->cants)
		add_neigh_to_neigh(&lem->prway[x], lem->start);
	i = 0;
	while ((x = chec(lem, ++i, -1, 0)) == 1)
		;
	if (x == -2 || x == -1)
		free_chek(lem, x);
	x = -1;
	while (++x < lem->cants)
		if (lem->prway[x]->room != lem->end)
			free_chek(lem, -2);
	free_chek(lem, 2);
	return (0);
}
