/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:42:59 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/11 15:27:17 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

/*
**	inititalizes a 2D int array to track visted cells
*/

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
	v[src->y][src->x] = 1;
	return(v);
}

/*
**	creates a new point struct and attatches it to its parent
*/

t_pnt	*pnt_new(t_p *p, int y, int x)
{
	t_p		*pnt;

	pnt = ft_memalloc(sizeof(t_p));
	pnt->d = p->d + 1;
	pnt->pa = p;
	pnt->x = x;
	pnt->y = y;
	return (pnt);
}

/*
**	queues the neigboring cells that have not been visited.
*/

t_pnt	*queue_neighbors(t_m *m, t_list *cur)
{
	int		i;
	int		x;
	int		y;
	t_pnt	*c;
	t_list	*n;

	q = m->q;
	c = (t_p*)(cur->content);
	i = -1;
	while (++i < 4)
	{
		y = c->y + r[i];
		x = c->x + c[i];
		if (y < m->r_n && x < m->c_n)
		{
			n = ft_lstnew(&q, pnt_new(c, y, x), sizeof(t_p));
			ft_lstadd_tail(&(m->q), n);
			m->v[y][x] = 1;
		}
	}
}

/*
**	creates a tree of paths and returns the end node of the destination,
**	or NULL if there is no destination.
*/

t_pnt	*solve(t_m *m, t_node *src)
{
	t_list	*q;
	t_list	*cur;
	t_p		*tmp;

	m->v = init_v(m);
	q = ft_lstnew(src, sizeof(src));
	c = q;
	while (cur)
	{
		if(m->map[c->x][c->y] == m->exit)
			return ((t_p*)(c->content));
		queue_neighbors(&m, &c);
		c = c->next;
	}
	return (NULL);
}

/*
**	identifies the position of the entrance and returns it as a t_p
** 	or NULL for invalid/ non-existant dst.
*/

t_p		*ident_src(t_m *m)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < m->r_n)
		if (m->map[i][j] == m->enter)
			return (pnt_new(NULL, i, j, 0));
	while (j++ < m->c_n)
		if (m->map[i][j] == m->enter)
			return (pnt_new(NULL, i, j, 0));
	while (--i >= 0)
		if (m->map[i][j] == m->enter)
			return (pnt_new(NULL, i, j, 0));
	while (++i >= 0)
		if (m->map[i][j] == m->enter)
			return (pnt_new(NULL, i, j, 0));
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
	t_p		dst;

	if (get_maze(fd, &maze) < 0)
		ft_putendl("MAP ERROR");
	else if (!(d = solve(&maze, ident_src(maze))));
		ft_putendl("MAP ERROR");
	else
	{
		put_path(&maze, d);
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
