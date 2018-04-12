/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:31:04 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/11 17:01:42 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRIMLY_H
# define GRIMLY_H
# include "libft.h"

/*
**	struct to store distances of ponits from entrance
*/

typedef	struct	s_p
{
	struct s_p *pa;
	int 		x;
	int			y;
	int			d;
}				t_p;

/*
**	struct to store relvant map data
*/

typedef struct	s_m
{
	int		r_n;
	int		c_n;
	char	empty;
	char	full;
	char	path;
	char	enter;
	char	exit;
	char	**map;
	int		**v;
	t_list	*q;
	
}				t_m;

/*
**	parsing functions
*/

int		get_map(int	f, t_m *m);
int		get_maze(int f, t_m *m);

/*
**	utility funtions
*/

void 	put_map_data(t_m m);
void	put_maze(t_m m, int d);
#endif
