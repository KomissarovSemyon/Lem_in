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
		ft_lstdel(&(cf->lem->buff_head), NULL);
		free(cf->lem);
	}
	free(cf);
	exit(0);
	return (0);
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
		if ((i = read_com(cf->lem, -1, 0, 0)) == 1)
			draw(cf->lem->rlist, cf);
		else if (i == -1 || i == -2)
			close1(cf);
	}
	if (but == 53)
		close1(cf);
	return (0);
}

void	vizual_way(t_cf *cf)
{
	int		l;

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
		read_input(cf->lem, NULL) == 1 || !cf->lem->rlist)
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
