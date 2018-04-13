/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:42:59 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/13 11:55:53 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

/*
**	inititalizes a 2D int array to track visted cells
*/

int		**init_v(t_m *m, t_p *src)
{
	int		**v;
	int		i;
	int		j;
	
	v = (int**)ft_memalloc(sizeof(int*) * m->r_n);
	i = -1;
	while (++i < m->r_n)
	{
		v[i] = (int*)ft_memalloc(sizeof(int) * m->c_n);
		j = -1;
		while (++j < m->c_n)
			v[i][j] = 0;
	}
	v[src->y][src->x] = 1;
	return(v);
}

/*
**	returns a code to indicate direction of wave propagation
*/

int		get_d(int y, int x)
{
	if (y == -1 && !x)
		return (1);
	else if (!y && x == -1)
		return (2);
	else if (!y && x == 1)
		return (3);
	else if (y == 1 && !x)
		return (4);
	return (0);
}

/*
**	creates a new point struct and attatches it to its parent
**	no more parents in this version
*/

t_p		*pnt_new(int y, int x, int yo, int xo)
{
	t_p		*pnt;

	pnt = ft_memalloc(sizeof(t_p));
	pnt->d = get_d(yo, xo);
	pnt->x = x;
	pnt->y = y;
	return (pnt);
}


/*
**	queues the neigboring cells that have not been visited.
*/

void	queue_neighbors(t_m *m, t_p *cur, int nr[4], int nc[4])
{
	int		i;
	int		x;
	int		y;

	i = -1;
	while (++i < 4)
	{
		y = cur->y + nr[i];
		x = cur->x + nc[i];
		if ((y >= 0 && y < m->r_n) && (x >= 0 && x < m->c_n))
		{
			if (!m->v[y][x] && m->map[y][x] != m->full)
				ft_enqueue(m->q, pnt_new(y, x, nr[i], nc[i]), sizeof(t_p));
		}
	}
}

/*
**	initialize row and column arrays used to find neigbors with ease
*/

void init_n(int r[4], int c[4])
{
	r[0] = -1;
	r[1] = 0;
	r[2] = 0;
	r[3] = 1;
	c[0] = 0;
	c[1] = -1;
	c[2] = 1;
	c[3] = 0; 
}

/*
**	creates a tree of paths and returns the end node of the destination,
**	or NULL if there is no destination.
*/

t_p		*solve(t_m *m, t_p *src)
{
	t_p		*cur;
	int	r[4];
	int	c[4];

	init_n(r, c); 
	m->v = init_v(m, src);
	m->q = ft_queuenw(src, sizeof(t_p));
	while (m->q->tail)
	{
		cur = (t_p*)ft_dequeue(m->q);
		queue_neighbors(m, cur, r, c);
		if(cur && m->map[cur->y][cur->x] == m->exit)
			return (cur);
		else if (cur)
			m->v[cur->y][cur->x] = cur->d;
		free(cur);
	}
	ft_memdel((void**)cur);
	return (NULL);
}

/*
**	identifies the position of the entrance and returns it as a t_p
** 	or NULL for invalid/ non-existant dst.
*/

t_p		*ident_src(t_m m)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < m.r_n)
		if (m.map[i][j] == m.enter)
			return (pnt_new(i, j, 0, 0));
	--i;
	while (++j < m.c_n)
		if (m.map[i][j] == m.enter)
			return (pnt_new(i, j, 0, 0));
	--j;
	while (--i >= 0)
		if (m.map[i][j] == m.enter)
			return (pnt_new(i, j, 0, 0));
	++i;
	while (--j >= 0)
		if (m.map[i][j] == m.enter)
			return (pnt_new(i, j, 0, 0));
	return (NULL);
}

/*
**	draws the path on the map from dst to src
*/

void	put_path(t_m *m, t_p *dst, t_p *src)
{
	int	i;
	int	j;
	int	**v;

	v = m->v;
	i = dst->y;
	j =	dst->x;
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
		m->map[i][j] = m->path;
	}
}

/*
**	parses, validates, solves, and prints a map from valid file descriptors given 
**	input, will display error messages appropriatly.
*/

void	grimly(int fd)
{
	t_m		maze;
	t_p		*src;
	t_p		*dst;

	if (get_maze(fd, &maze) < 0)
		ft_putendl("MAP ERROR");
	else if (!(dst = solve(&maze, (src = ident_src(maze)))))
		ft_putendl("MAP ERROR");
	else
	{
		put_path(&maze, dst, src);
		put_maze(maze, 0);
	}
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
