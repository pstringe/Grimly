/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 08:25:56 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/13 11:55:32 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"
void		ft_lstadd_tail(t_list **head, t_list *new)
{
	t_list	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_queue		*ft_queuenw(void *n, size_t size)
{
	t_queue	*q;
	t_list	*tmp;

	q = (t_queue*)ft_memalloc(sizeof(t_queue));
	tmp = ft_lstnew(n, size);
	q->head = &tmp;
	q->tail	= q->head;
	return (q);
}

void		ft_enqueue(struct s_queue *q, void *n, size_t size)
{	
	t_list	**tail;
	t_list	*tmp;

	tail = q->tail;
	tmp = ft_lstnew(n, size);
	(*tail)->next = tmp;
	tail = &tmp;
	q->tail = tail;

}

void		*ft_dequeue(struct s_queue *q)
{
	t_list		**head;
	t_list		*tmp;
	void		*t;

	head = q->head;
	if (!(*head))
		return (NULL);
	tmp = *head;
	t = (void*)(tmp->content);
	*q->head = tmp->next;
	ft_memdel((void**)&tmp);
	return (t);
}
