/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:33:37 by aaudeber          #+#    #+#             */
/*   Updated: 2023/10/02 16:01:06 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_list	*ft_lstnew(int id)
{
	t_list	*new;
	pthread_mutex_t	fork_r;
	int	is_error;

	is_error = pthread_mutex_init(&fork_r, NULL);	
	if (is_error)
		handle_error("phtread_init");

	new = (t_list *)ft_calloc(sizeof(t_list), 1);
	if (!new)
		return (NULL);
	new->philo_id = id;
	new->fork_r = &fork_r;
	new->next = NULL;
	return (new);
}
