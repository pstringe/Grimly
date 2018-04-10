/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:42:59 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/10 10:33:59 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

void 	put_map_data(t_m m)
{
	ft_putstr("row no:\t\t");
	ft_putnbr(m.r_n);
	ft_putchar('\n');
	ft_putstr("col no:\t\t");
	ft_putnbr(m.c_n);
	ft_putchar('\n');
	ft_putstr("empty char:\t");
	ft_putchar(m.empty);
	ft_putchar('\n');
	ft_putstr("full char:\t");
	ft_putchar(m.full);
	ft_putchar('\n');
	ft_putstr("path char:\t");
	ft_putchar(m.path);
	ft_putchar('\n');
	ft_putstr("enter char:\t");
	ft_putchar(m.enter);
	ft_putchar('\n');
	ft_putstr("exit char:\t");
	ft_putchar(m.exit);
	ft_putstr("\n\n");
}

void	put_maze(t_m m, int d)
{
	int		i;
	
	if (d)
		put_map_data(m);
	i = -1;
	while (m.map[++i])
	{
		ft_putendl(m.map[i]);
	}
}

int		get_map(int	f, t_m *m)
{
	char	**map;
	char 	*row;
	int		i;

	map = (char **)ft_memalloc(sizeof(char*) * m->r_n + 1);
	map[m->r_n] = NULL;
	i = 0;
	while (get_next_line(f, &row) > 0 && i < m->r_n)
	{
		if ((int)ft_strlen(row) != m->c_n)
			return (-1);
		map[i] = ft_strdup(row);
		free(row);
		i++;
	}
	m->map = map;
	return (0);
}

int		get_maze(int f, t_m *m)
{
	char	*head;
	char	*i;

	if(get_next_line(f, &head) < 0)
		return (-1);
	*(i = ft_strchr(head, 'x')) = '\0';
	m->r_n = ft_atoi(ft_strdup(head));
	m->c_n = ft_atoi(ft_strdup(i ? i + 1 : NULL));
	while(*(++i) >= '0' && *i <= '9');
	m->full = *i++;
	m->empty = *i++;
	m->path = *i++;
	m->enter = *i++;
	m->exit = *i++;
	if (*i || get_map(f, m) < 0)
		return (-1);
	else
		return (0);	
}

int		solve(t_m *m)
{
	if (m)
	{
		//print_maze(m);
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
	else
		put_maze(maze, 0);
	/*
	if (solve(&maze))
		put_map(maze.map);
	else
		ft_putendl("MAP ERROR");
	*/
}

int		main(int argc, char **argv)
{
	int	i;
	if (argc >= 2)
	{
		i = 0;
		while (argv[++i])
			grimly(open(argv[i], O_RDONLY));
	}
	return(0);
}
