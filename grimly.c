/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:42:59 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/10 11:55:59 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int		**init_v(t_m *m)
{
	int		**v;
	int		i;
	int		j;
	
	v = int(int**)ft_memalloc(sizeof(int*) * m->r_n);
	i = -1;
	while (++i < r_n)
	{
		v[i] = (int*)ft_memalloc(sizeof(int) * m->c_n);
		j = -1;
		while (++j < c_n)
			v[i][j] = 0;
	}
	return(v);
}

int		solve(t_m *m, t_node *src)
{
	int		**v;
	t_list	*q;

	v = init_v(m);
	q = ft_lstnew(src, sizeof(src));
	
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
