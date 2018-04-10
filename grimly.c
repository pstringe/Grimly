/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:42:59 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/09 21:04:21 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int		get_map(int	f, t_m *m)
{
	char	**map;
	char 	*row;
	int		i;

	map = (char **)ft_memalloc(sizeof(char*) * r_n);
	i = 0;
	while (get_next_line(f, &row) > 0)
	{
		if (ft_strlen(row) != m->c_n)
			return (-1);
		map[i] = ft_strdup(row);
		free(row);
		i++;
	}
}

int		get_maze(int f, t_m *m)
{
	char	*head;
	char	*i;

	if(get_next_line(f, &head) < 0)
		return (-1);
	(i = ft_strchr(head, 'x')) = '\0';
	m->r_n = ft_atoi(ft_strdup(head));
	m->c_n = ft_atoi(ft_strdup(i ? i + 1 : NULL));
	while(++i >= '0' && i <= '9');
	m->full = *i++;
	m->path = *i++;
	m->empty = *i++;
	m->enter = *i++;
	m->exit = *i++;
	if (i || !get_map(f, m));
		return (-1);
	else
		return (0);	
}

int		solve(t_m *m)
{
	if (m)
	{
		print_maze(m);
		return (1);
	}
	else
		return (0);
}

void	grimly(int fd)
{
	t_m		maze;

	if (get_maze(fd, &maze) < 0)
		ft_putendl("MAP ERROR");
	if (solve(&maze))
		put_map(maze.map);
	else
		ft_putendl("MAP ERROR");
}

int		main(int argc, char **argv)
{
	int	i;
	if (argc >= 2)
	{
		i = -1;
		while (argv[++i])
			grimly(open(argv[i], O_RDONLY));
	}
	return(0);
}
