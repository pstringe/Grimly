/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:31:04 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/10 14:53:24 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRIMLY_H
# define GRIMLY_H
# include "libft.h"

/*
**	used to quickly locate neiboring positions on the map;
*/

g_r = {-1, 0, 0, 1};
g_c = {1, 0, -1, 0};

/*
**	struct to store distances of ponits from entrance
*/

typedef	struct	s_p
{
	int x;
	int	y;
	int	d;
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
}				t_m;

#endif
