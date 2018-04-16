/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 08:03:41 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/16 08:32:04 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

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
