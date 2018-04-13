/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:31:04 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/13 09:42:18 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRIMLY_H
# define GRIMLY_H
# include "libft.h"

/*
**	queue struct
*/

typedef struct	s_queue
{
	struct s_list	**head;
	struct s_list	**tail;
}				t_queue;

/*
**	struct to store distances of ponits from entrance
*/

typedef	struct	s_p
{
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
	t_queue	*q;
}				t_m;

/*
**	parsing functions
*/

int		get_map(int	f, t_m *m);
int		get_maze(int f, t_m *m);

/*
**	queue functions
*/

t_queue		*ft_queuenw(void *n, size_t size);
void		*ft_dequeue(struct s_queue *q);
void		ft_enqueue(struct s_queue *q, void *n, size_t size);
/*
**	utility funtions
*/

void 	put_map_data(t_m m);
void	put_maze(t_m m, int d);
#endif
