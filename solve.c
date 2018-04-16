/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 08:00:28 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/16 08:35:37 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

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
		assert(cur);
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

void	init_n(int r[4], int c[4])
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

t_p			*solve(t_m *m, t_p *src)
{
	t_p		*cur;
	int	r[4];
	int	c[4];

	init_n(r, c); 
	m->v = init_v(m, src);
	m->q = ft_queuenw(src, sizeof(t_p));
	while ((cur = (t_p*)ft_dequeue(m->q)))
	{
		queue_neighbors(m, cur, r, c);
		if (cur)
			m->v[cur->y][cur->x] = (cur->d) ? cur->d : -1;
		if(cur && m->map[cur->y][cur->x] == m->exit)
			return (cur);
		ft_memdel((void**)&(cur));
	}
	ft_memdel((void**)&cur);
	return (NULL);
}
