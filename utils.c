/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 11:32:03 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/16 09:24:52 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

/*
**	displays maze related data
*/

void	put_map_data(t_m m)
{
	ft_putstr("row no:\t\t");
	ft_putnbr(m.r_n);
	ft_putchar('\n');
	ft_putstr("col no:\t\t");
	ft_putnbr(m.c_n);
	ft_putchar('\n');
	ft_putstr("empty char:\t");
	ft_putchar(m.empty);
	ft_putchar('\n');
	ft_putstr("full char:\t");
	ft_putchar(m.full);
	ft_putchar('\n');
	ft_putstr("path char:\t");
	ft_putchar(m.path);
	ft_putchar('\n');
	ft_putstr("enter char:\t");
	ft_putchar(m.enter);
	ft_putchar('\n');
	ft_putstr("exit char:\t");
	ft_putchar(m.exit);
	ft_putstr("\n\n");
}

/*
**	displays maze with optional data
*/

void	put_maze(t_m m, int d)
{
	int		i;

	if (d)
		put_map_data(m);
	i = -1;
	while (m.map[++i])
	{
		ft_putendl(m.map[i]);
	}
}
