/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:33:15 by amerlon-          #+#    #+#             */
/*   Updated: 2019/03/05 20:50:28 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

static int	add_to_buffer(t_lemin *lem, char *line)
{
	if (!lem || !line)
		return (-1);
	if (!lem->buff_head)
	{
		ft_lstadd(&(lem->buff_head),
			ft_lstnew(ft_strdup(line), ft_strlen(line) + 1));
		lem->buff_tail = lem->buff_head;
	}
	else
	{
		lem->buff_tail->next = ft_lstnew(ft_strdup(line), ft_strlen(line) + 1);
		lem->buff_tail = lem->buff_tail->next;
	}
	return (1);
}

static int	ft_xatoi(const char *str)
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

static int	add_list_unique(t_list1 **st, char *name, int x, int y)
{
	t_list1 *prev;
	t_list1 *t;
	t_list1 *t1;

	if (!name || !(t = (t_list1 *)ft_memalloc(sizeof(t_list1))))
		return (-1);
	t->name = name;
	t->x = x;
	t->y = y;
	if (!(*st))
		*st = t;
	else
	{
		t1 = *st;
		prev = NULL;
		while (t1)
			if (ft_strcmp(t1->name, name) == 0 || (t1->x == x && t1->y == y))
			{
				free(t);
				return (-1);
			}
			else
			{
				prev = t1;
				t1 = t1->next;
			}
		prev->next = t;
	}
	return (1);
}

static int	connect_to_list(t_lemin *lem, char *name, int room_type)
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

/*
**	room_type = 0 - room
**	room_type = 1 - start
**	room_type = 2 - end
*/

static int	add_room_to_lem(t_lemin *lem, char *line, int room_type)
{
	int		i;
	int		x;
	int		y;
	char	*name;

	//NAME
	if (!ft_strchr(line, ' '))
		return (-1);
	i = ft_strchr(line, ' ') - line;
	line[i] = '\0';
	name = ft_strdup(line);
	if (!name || name[0] == 0 || name[0] == 'L')
		return (-ft_strdel(&name));
	line = line + i + 1;
	//X
	if (!ft_strchr(line, ' '))
		return (-1);
	i = ft_strchr(line, ' ') - line;
	line[i] = '\0';
	x = ft_xatoi(line);
	if (x == 0 && (!ft_isnumeric(line) || line[0] != '0'))
		return (-ft_strdel(&name));
	line = line + i + 1;
	//Y
	y = ft_xatoi(line);
	if (y == 0 && (!ft_isnumeric(line) || line[0] != '0'))
		return (-ft_strdel(&name));
	// !!!НАДО в add_list добавлять только уникальные поля(name)!!!
	i = add_list_unique(&(lem->rlist), name, x, y);
	if (room_type > 0 && i != -1)
		i = connect_to_list(lem, name, room_type);
	if (i == -1)
		free(name);
	return (i);
}

static int	add_neigh_to_lem(t_lemin *lem, char *str)
{
	int	i;
	t_list1	*room1;
	t_list1	*room2;

	if (!ft_strchr(str, '-'))
		return (-1);
	i = ft_strchr(str, '-') - str;
	str[i] = '\0';
	if (ft_strcmp(str, str + i + 1) == 0)
		return (-1);
	// Add only unique(do not add duplicates)
	if (!(room1 = find_list(lem->rlist, str)) ||
		!(room2 = find_list(lem->rlist, str + i + 1)))
		return (-1);
	add_neigh(room1, room2);
	add_neigh(room2, room1);
	return (1);
}

/*
**	invalid - -1
**	commmet - 0
**	count_ants - 1
**	room - 2
**	neigh - 3
**	cmd start - 4
**	cmd end - 5
*/

static int	get_type(char *line)
{
	int	nbr;

	if (line[0] == '#' && line[1] == '#' && ft_strcmp(line + 2, "start") == 0)
		return (4);
	if (line[0] == '#' && line[1] == '#' && ft_strcmp(line + 2, "end") == 0)
		return (5);
	if (line[0] == '#')
		return (0);
	if (ft_strnchr(line, ' ', 2) != -1)
		return (2);
	if (ft_strchr(line, '-'))
		return (3);
	if (!ft_isnumeric(line))
		return (-1);
	return (1);
}

static void	parse_ants(t_lemin *lem, char *line, int *last_type)
{
	*last_type = 2;
	lem->cants = ft_xatoi(line);
}

static void	parse_room(t_lemin *lem, char *line, int *last_type, int *type)
{
	*last_type = 2;
	if (add_room_to_lem(lem, line, 0) == -1)
		*type = -1;
}

static void	parse_neigh(t_lemin *lem, char *line, int *last_type, int *type)
{
	*last_type = 3;
	if (add_neigh_to_lem(lem, line) == -1)
		*type = -1;
}

static int	exec_cmd(t_lemin *lem, int type, int fd)
{
	char	*line;
	int		t;

	if (ft_gnl(fd, &line) < 0)
		return (-1);
	add_to_buffer(lem, line);
	t = get_type(line);
	if (t != 2)
		return (-ft_strdel(&line));
	if (type == 4)
		return (add_room_to_lem(lem, line, 1) == -1 ?
			-ft_strdel(&line) : ft_strdel(&line) + 1); 
	if (type == 5)
		return (add_room_to_lem(lem, line, 2) == -1 ?
			-ft_strdel(&line) : ft_strdel(&line) + 1);
	return (-1);
}

static int	check_data(t_lemin *lem)
{
	if (lem->cants <= 0 || !lem->start || !lem->end ||
		(lem->start->x == lem->end->x && lem->start->y == lem->end->y))
		return (-1);
	return (1);
}

int	read_input(t_lemin *lem, char *name, int isnviz)
{
	int		fd;
	int		type;
	int		last_type;
	char	*line;

	isnviz = 0;
	if (!lem)
		return (-1);
	if ((fd = !name ? 0 : open(name, O_RDONLY)) < 0)
		return (-1);
	last_type = 0;
	type = 0;
	while (ft_gnl(fd, &line) > 0 && type >= 0)
	{
		add_to_buffer(lem, line);
		type = get_type(line);
		if (type == -1 || (last_type == 2 && type == 1) ||
			(last_type == 3 && type == 1) || (last_type == 3 && type == 2))
			return (-ft_strdel(&line));
		if (type > 3)
			type = exec_cmd(lem, type, fd);
		else if (type == 1)
			parse_ants(lem, line, &last_type);
		else if (type == 2)
			parse_room(lem, line, &last_type, &type);
		else if (type == 3)
			parse_neigh(lem, line, &last_type, &type);
		ft_strdel(&line);
	}
	close(fd);
	return (type == -1 ? -1 : check_data(lem));
}

void	print_buff(t_list *head)
{
	while (head)
	{
		ft_putendl(head->content);
		head = head->next;
	}
}
