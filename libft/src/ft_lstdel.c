/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 18:46:00 by amerlon-          #+#    #+#             */
/*   Updated: 2019/03/09 15:50:54 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	default_del(void *mem, size_t size)
{
	size = 0;
	free(mem);
}

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*now;
	t_list	*tmp;

	if (!alst || !(*alst))
		return ;
	if (!del)
	{
		ft_lstdel(alst, &default_del);
		return ;
	}
	now = *alst;
	while (now)
	{
		tmp = now->next;
		ft_lstdelone(&now, del);
		now = tmp;
	}
	*alst = NULL;
}
