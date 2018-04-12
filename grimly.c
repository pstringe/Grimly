/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:42:59 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/11 18:03:13 by pstringe         ###   ########.fr       */
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
**	creates a new point struct and attatches it to its parent
*/

t_p		*pnt_new(t_p *p, int y, int x)
{
	t_p		*pnt;

	pnt = ft_memalloc(sizeof(t_p));
	pnt->d = (p) ? p->d + 1 : 0;
	pnt->pa = p;
	pnt->x = x;
	pnt->y = y;
	return (pnt);
}

/*
**	queues the neigboring cells that have not been visited.
*/

void	queue_neighbors(t_m *m, t_list *cur, int nr[4], int nc[4])
{
	int		i;
	int		x;
	int		y;
	t_p		*c;
	t_list	*n;

	c = (t_p*)(cur->content);
	i = -1;
	while (++i < 4)
	{
		y = c->y + nr[i];
		x = c->x + nc[i];
		if ((y >= 0 && y < m->r_n) && (x >= 0 && x < m->c_n))
		{
			if (!m->v[y][x] && m->map[y][x] != m->full)
			{
				n = ft_lstnew(pnt_new(c, y, x), sizeof(t_p));
				ft_lstadd_tail(&(m->q), n);
			}
		}
	}
}

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
	t_list	*cur;
	t_p		*tmp;
	int	r[4];
	int	c[4];

	init_n(r, c); 
	m->v = init_v(m, src);
	m->q = ft_lstnew(src, sizeof(t_p));
	cur = m->q;
	while (cur)
	{
		queue_neighbors(m, cur, r, c);
		tmp = (cur) ? (t_p*)(cur->content) : NULL;
		if(tmp && m->map[tmp->y][tmp->x] == m->exit)
			return (tmp);
		else if (tmp)
			m->v[tmp->y][tmp->x] = 1;
		cur = cur->next;
	}
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
			return (pnt_new(NULL, i, j));
	--i;
	while (++j < m.c_n)
		if (m.map[i][j] == m.enter)
			return (pnt_new(NULL, i, j));
	--j;
	while (--i >= 0)
		if (m.map[i][j] == m.enter)
			return (pnt_new(NULL, i, j));
	++i;
	while (--j >= 0)
		if (m.map[i][j] == m.enter)
			return (pnt_new(NULL, i, j));
	return (NULL);
}

/*
**	draws the path on the map from dst to src
*/

void	put_path(t_m *m, t_p *dst)
{
	t_p		*tmp;

	tmp = dst->pa;
	while (tmp)
	{
		m->map[tmp->y][tmp->x] = m->path;
		tmp = tmp->pa;
	}
}

/*
**	parses, validates, solves, and prints a map from valid file descriptors given 
**	input, will display error messages appropriatly.
*/

void	grimly(int fd)
{
	t_m		maze;
	t_p		*dst;

	if (get_maze(fd, &maze) < 0)
		ft_putendl("MAP ERROR");
	else if (!(dst = solve(&maze, ident_src(maze))))
		ft_putendl("MAP ERROR");
	else
	{
		put_path(&maze, dst);
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
