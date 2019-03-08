/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinnch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semyonkomissarov <semyonkomissarov@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 14:09:57 by amerlon-          #+#    #+#             */
/*   Updated: 2019/02/13 11:40:18 by semyonkomis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinnch(char **str, char c, int n, int flag)
{
	int		i;
	char	*res;

	if (!str || !(*str))
		return (NULL);
	if (n <= 0)
		return (ft_strdup(*str));
	res = ft_strnew(ft_strlen(*str) + n);
	if (!res)
		return (NULL);
	i = -1;
	while ((*str)[++i])
		res[i] = (*str)[i];
	while (n--)
		res[i++] = c;
	if (flag)
		ft_strdel(str);
	return (res);
}
