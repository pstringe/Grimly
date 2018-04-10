/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 11:35:29 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/10 11:38:13 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

/*
**	obtains 2D map of maze
*/

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

/*
**	parses first line of maze file to initialize maze structure
*/

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
