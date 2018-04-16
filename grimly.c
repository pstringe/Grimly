/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:42:59 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/16 08:46:50 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

void	put_path(t_m *m, t_p *dst, t_p *src)
{
	int	i;
	int	j;
	int	**v;

	v = m->v;
	i = dst->y;
	j = dst->x;
	while (!(i == src->y && j == src->x))
	{
		if (v[i][j] == 1)
			i++;
		else if (v[i][j] == 2)
			j++;
		else if (v[i][j] == 3)
			j--;
		else if (v[i][j] == 4)
			i--;
		m->map[i][j] = (v[i][j] != -1) ? m->path : m->map[i][j];
	}
}

void	destroy_maze(t_m *m)
{
	int	i;

	i = -1;
	while (++i < m->r_n)
	{
		ft_memdel((void**)&(m->map[i]));
		ft_memdel((void**)&(m->v[i]));
	}
	ft_memdel((void**)&(m->map));
	ft_memdel((void**)&(m->v));
	ft_memdel((void**)&(m->q));
}

int		grimly(int fd)
{
	t_m		maze;
	t_p		*src;
	t_p		*dst;

	if (get_maze(fd, &maze) < 0)
		return (0);
	src = ident_src(maze);
	dst = solve(&maze, src);
	if (!dst)
		return (0);
	else
	{
		put_path(&maze, dst, src);
		put_maze(maze, 0);
		ft_memdel((void**)&src);
		destroy_maze(&maze);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int	i;

	if (argc >= 2)
	{
		i = 0;
		while (++i < argc)
			if (!grimly(open(argv[i], O_RDONLY)))
				write(2, "MAP ERROR\n", 10);
	}
	return (0);
}
