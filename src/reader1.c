/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:33:15 by amerlon-          #+#    #+#             */
/*   Updated: 2019/03/09 15:55:21 by amerlon-         ###   ########.fr       */
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
			ft_lstnew((line), ft_strlen(line) + 1));
		lem->buff_tail = lem->buff_head;
	}
	else
	{
		lem->buff_tail->next = ft_lstnew((line), ft_strlen(line) + 1);
		lem->buff_tail = lem->buff_tail->next;
	}
	return (1);
}

static int	exec_cmd(t_lemin *lem, int type, int fd)
{
	char	*line;
	int		t;

	if (ft_gnl(fd, &line) < 0)
	{
		free(line);
		return (-1);
	}
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
		return (-ft_strdel(&line));
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

int			get_type(char *line)
{
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

static int	check_data(t_lemin *lem)
{
	if (lem->cants <= 0 || !lem->start || !lem->end ||
		(lem->start->x == lem->end->x && lem->start->y == lem->end->y))
		return (-1);
	return (1);
}

int			read_input(t_lemin *lem, char *name)
{
	int		i[3];
	char	*line;

	if (!lem || (i[0] = !name ? 0 : open(name, O_RDONLY)) < 0)
		return (-1);
	i[2] = 0;
	i[1] = 0;
	while (ft_gnl(i[0], &line) > 0 && i[1] >= 0)
	{
		add_to_buffer(lem, line);
		i[1] = get_type(line);
		if (i[1] == -1 || (i[2] == 2 && i[1] == 1) ||
			(i[2] == 3 && i[1] == 1) || (i[2] == 3 && i[1] == 2))
			return (-ft_strdel(&line));
		if (i[1] > 3)
			i[1] = exec_cmd(lem, i[1], i[0]);
		else if (i[1] == 1 || i[1] == 2)
			i[1] == 1 ? parse_ants(lem, line, &i[2]) :
						parse_room(lem, line, &i[2], &i[1]);
		i[1] == 3 ? parse_neigh(lem, line, &i[2], &i[1]) : (0);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(i[0]);
	return (i[1] == -1 ? -1 : check_data(lem));
}
