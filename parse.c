/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 11:35:29 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/16 08:31:48 by pstringe         ###   ########.fr       */
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
**	obtains 2D map of maze
*/

int		get_map(int	f, t_m *m)
{
	char	**map;
	char 	*row;
	int		i;

	map = (char**)ft_memalloc(sizeof(char*) * (m->r_n + 1));
	map[m->r_n] = NULL;
	i = 0;
	while (get_next_line(f, &row) > 0 && i < m->r_n)
	{
		if ((int)ft_strlen(row) != m->c_n)
		{
			ft_memdel((void**)&row);
			return (-1);
		}
		map[i] = ft_strdup(row);
		ft_memdel((void**)&row);
		i++;
	}
	m->map = map;
	return (0);
}

/*
**	parses first line of maze file to initialize maze structure
*/

int		get_maze(int f, t_m *m)
{
	char	*head;
	char	*i;
	char 	c;
	char 	*cn;

	if(get_next_line(f, &head) < 0)
		return (-1);
	*(i = ft_strchr(head, 'x')) = '\0';
	m->r_n = ft_atoi(ft_strdup(head));
	m->c_n = ft_atoi((cn = ft_strdup(i ? i + 1 : NULL)));
	while(*(++i) >= '0' && *i <= '9');
	m->full = *i++;
	m->empty = *i++;
	m->path = *i++;
	m->enter = *i++;
	m->exit = *i++;
	c = *i;
	ft_memdel((void**)&cn);
	ft_memdel((void**)&head);
	if (c || get_map(f, m) < 0)
		return (-1);
	else
		return (0);	
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
