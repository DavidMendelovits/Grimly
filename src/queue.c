/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:16:49 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/26 17:28:54 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

void			push(t_list **head, void *new_data, size_t size)
{
	t_list			*new;

	new = (t_list *)malloc(sizeof(*new));
	new->data = malloc(size);
	ft_memcpy(new->data, new_data, size);
	new->size = size;
	if (!(*head))
	{
		new->next = NULL;
	}
	else
	{
		new->next = *head;
	}
	*head = new;
}

void			push_back(t_list **head, void *new_data, size_t size)
{
	t_list					*new;
	t_list					*tmp;

	new = (t_list *)malloc(sizeof(*new));
	new->data = malloc(size);
	ft_memcpy(new->data, new_data, size);
	new->size = size;
	new->next = NULL;
	tmp = *head;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

void			*pop(t_list **head)
{
	void					*data;
	t_list					*new;

	data = malloc((*head)->size);
	ft_memcpy(data, (*head)->data, (*head)->size);
	new = (*head)->next;
	free((*head)->data);
	free(*head);
	*head = new;
	return (data);
}
