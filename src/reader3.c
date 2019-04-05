/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:33:15 by amerlon-          #+#    #+#             */
/*   Updated: 2019/03/09 14:27:49 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

/*
**	room_type = 0 - room
**	room_type = 1 - start
**	room_type = 2 - end
*/

int			parse_line_room(char *line, int *x, int *y, char **name)
{
	int	i;

	if (!ft_strchr(line, ' '))
		return (-1);
	i = ft_strchr(line, ' ') - line;
	line[i] = '\0';
	*name = ft_strdup(line);
	if (!*name || (*name)[0] == 0 || (*name)[0] == 'L')
		return (-ft_strdel(name));
	line = line + i + 1;
	if (!ft_strchr(line, ' '))
		return (-ft_strdel(name));
	i = ft_strchr(line, ' ') - line;
	line[i] = '\0';
	*x = ft_xatoi(line);
	if (*x == 0 && (!ft_isnumeric(line) || line[0] != '0'))
		return (-ft_strdel(name));
	line = line + i + 1;
	*y = ft_xatoi(line);
	if (*y == 0 && (!ft_isnumeric(line) || line[0] != '0'))
		return (-ft_strdel(name));
	return (1);
}

int			add_room_to_lem(t_lemin *lem, char *line, int room_type)
{
	int		i;
	int		x;
	int		y;
	char	*name;

	if ((room_type == 1 && lem->start) || (room_type == 2 && lem->end))
		return (-1);
	i = parse_line_room(line, &x, &y, &name);
	if (i == -1)
		return (-1);
	i = add_list_unique(&(lem->rlist), name, x, y);
	if (room_type > 0 && i != -1)
		i = connect_to_list(lem, name, room_type);
	if (i == -1)
		free(name);
	return (i);
}

static int	add_neigh_to_lem(t_lemin *lem, char *str)
{
	int		i;
	t_list1	*room1;
	t_list1	*room2;

	if (!ft_strchr(str, '-'))
		return (-1);
	i = ft_strchr(str, '-') - str;
	str[i] = '\0';
	if (ft_strcmp(str, str + i + 1) == 0)
		return (-1);
	if (!(room1 = find_list(lem->rlist, str)) ||
		!(room2 = find_list(lem->rlist, str + i + 1)))
		return (-1);
	add_neigh(room1, room2);
	add_neigh(room2, room1);
	return (1);
}

void		parse_room(t_lemin *lem, char *line, int *last_type, int *type)
{
	*last_type = 2;
	if (add_room_to_lem(lem, line, 0) == -1)
		*type = -1;
}

void		parse_neigh(t_lemin *lem, char *line, int *last_type, int *type)
{
	*last_type = 3;
	if (add_neigh_to_lem(lem, line) == -1)
		*type = -1;
}
