/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semyonkomissarov <semyonkomissarov@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:02:56 by amerlon-          #+#    #+#             */
/*   Updated: 2019/02/13 11:24:28 by semyonkomis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putstr(char const *s)
{
	int	i;

	if (!s)
		return (-1);
	i = ft_strlen(s);
	write(1, s, i);
	return (i);
}
