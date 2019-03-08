/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semyonkomissarov <semyonkomissarov@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:08:44 by amerlon-          #+#    #+#             */
/*   Updated: 2019/02/13 11:25:05 by semyonkomis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putstr_fd(char const *s, int fd)
{
	int	i;

	i = ft_strlen(s);
	write(fd, s, i);
	return (i);
}
